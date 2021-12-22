#include "mem.h"
extern BLOCK_HEADER *first_header;

BLOCK_HEADER *get_next_header(BLOCK_HEADER *current, int block_size)
{
	return (BLOCK_HEADER *)((unsigned long)current + block_size);
}

int get_padding(BLOCK_HEADER *current)
{
	//recompute padding
	int padding = 0;
	while (((current->payload) + padding + 8) % 16 != 0)
	{
		padding++;
	}
	return padding;
}

void set_allocate(BLOCK_HEADER *current, int size)
{
	//set size_alloc to odd
	current->payload = size;
	current->size_alloc = 8 + size + get_padding(current);

	if (current->size_alloc % 2 == 0)
	{
		current->size_alloc += 1;
	}
}

int alloc;
int block_size;
int padding;
// return a pointer to the payload
// if a large enough free block isn't available, return NULL
void *Mem_Alloc(int size)
{
	BLOCK_HEADER *current = first_header;
	while (1)
	{
		alloc = current->size_alloc & 1;
		block_size = current->size_alloc & 0xFFFFFFFE;
		padding = block_size - 8 - (current->payload);

		// Current is not allocated
		if (alloc == 0)
		{
			// Current header has enough space
			if (current->payload >= size)
			{
				break;
			}
		}

		// At the last block
		if (current->size_alloc == 1)
		{
			// Return null, no block with enough space found
			return NULL;
		}

		// Get the next header
		current = get_next_header(current, block_size);
	}

	// allocate the block
	set_allocate(current, size);
	padding = get_padding(current);

	int *payload_pointer = (int *)((unsigned long)current + 8);
	int next_header_location = 8 + size + padding;

	if (block_size - current->payload - padding - 8 <= 0)
	{
		return payload_pointer;
	}

	BLOCK_HEADER *new_header = (BLOCK_HEADER *)((unsigned long)current + next_header_location);
	new_header->size_alloc = block_size - next_header_location;
	new_header->payload = block_size - next_header_location - 8;

	return payload_pointer;
}

int isFree(BLOCK_HEADER *current)
{
	if ((current->size_alloc & 1) == 0)
	{
		return 1;
	}
	return 0;
}
// return 0 on success
// return -1 if the input ptr was invalid
int Mem_Free(void *ptr)
{
	BLOCK_HEADER *current = first_header;
	// traverse the list and check all pointers to find the correct block
	while (1)
	{
		// Pointer locations of variables the user might be looking for
		void *user_pointer = (void *)((unsigned long)current + 8);
		block_size = current->size_alloc & 0xFFFFFFFE;

		// Valid given user pointer
		if (user_pointer == ptr)
		{
			break;
		}

		// Invalid given user pointer
		if (current->size_alloc == 1)
		{
			return -1;
		}

		// Get the next header
		current = get_next_header(current, block_size);
	}
	// free the block
	if (current->size_alloc % 2 != 0)
	{
		current->size_alloc -= 1;
	}

	int padding = get_padding(current);
	if (padding > 0)
	{
		current->payload += padding;
	}

	// coalesce adjacent free blocks
	for (int i = 0; i < 2; i++)
	{
		current = first_header;
		while (1)
		{
			block_size = current->size_alloc & 0xFFFFFFFE;

			// Adjecent header
			BLOCK_HEADER *adjacent_header = get_next_header(current, block_size);
			// Block size of adjacent header
			int adjacent_block_size = adjacent_header->size_alloc & 0xFFFFFFFE;

			// Header following adjacent header
			BLOCK_HEADER *final_header = get_next_header(adjacent_header, adjacent_block_size);
			// Block size of that header
			int final_block_size = (unsigned long)final_header - (unsigned long)adjacent_header;

			// If current header is free and next header is free
			if (isFree(current) && isFree(adjacent_header))
			{
				current->size_alloc += final_block_size;
				current->payload += adjacent_block_size;
			}

			if (current->size_alloc == 1)
			{
				break;
			}
			current = get_next_header(current, block_size);
		}
	}
	return -1;
}
