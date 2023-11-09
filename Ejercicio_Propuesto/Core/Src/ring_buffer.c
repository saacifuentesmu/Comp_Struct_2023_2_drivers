

#include "ring_buffer.h"


void ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *buffer, uint16_t capacity)
{
	/*parameter initialization*/
	ring_buffer->buffer = buffer;
	ring_buffer->capacity = capacity;

	ring_buffer->head  = 0;
	ring_buffer->tail = 0;
	ring_buffer->is_full = 0;
}
/*This function adds a data in the ring buffer*/
uint8_t ring_buffer_put(ring_buffer_t *ring_buffer, uint8_t data)
{
	ring_buffer->buffer[ring_buffer->head] = data; // put the data where the head is

	ring_buffer->head = (ring_buffer->head + 1) % ring_buffer->capacity; // When the counter reaches the end of memory, the counter is reset to write data again

	/* another method for when the counter is full
	if(ring_buffer->head > ring_buffer->capacity)
	{
		ring_buffer->head;
	}*/

	//If the head has already reached the end of the data, it returns and restarts to write the data again.
	//a buffer is full when the head reaches the tail
	if(ring_buffer->is_full != 0)
	{
		ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity; //If the buffer is still not full, the head moves one more position.
	}

	if(ring_buffer->head == ring_buffer->tail)
	{
		ring_buffer->is_full = 1;
		return 0;
	}
	return 1;
}
/*This function reads data a from ring buffer*/

uint8_t ring_buffer_get(ring_buffer_t *ring_buffer, uint8_t *data)
{
	if ((ring_buffer->is_full != 0) || (ring_buffer->tail != ring_buffer->head))
	{
		*data = ring_buffer->buffer[ring_buffer->tail];
		ring_buffer->tail = (ring_buffer->tail + 1) % ring_buffer->capacity; // actualizar el indice de la cola
		ring_buffer->is_full = 0; //clean the flag is full
	}
	return 0;
}
/*This function return the ring buffer size*/
uint16_t ring_buffer_size(ring_buffer_t *ring_buffer)
{
	uint16_t size = 0;
	if((ring_buffer->is_full == 0) && (ring_buffer->tail <= ring_buffer->head))
	{
		size = ring_buffer->head - ring_buffer->tail;
	}
	else
	{
		size = ring_buffer->head + (ring_buffer->capacity - ring_buffer->tail);
	}

	return size;
}
/*this buffer return a value if the ring buffer is empty*/
uint8_t ring_buffer_is_empty(ring_buffer_t *ring_buffer)
{
	if((ring_buffer->head == ring_buffer->tail) && (ring_buffer->is_full != 1))
	{
		return 1; // Is empty
	}
	return 0; // with some information
}
uint8_t ring_buffer_is_full(ring_buffer_t *ring_buffer)
{
	return (ring_buffer->is_full=0);
}

void ring_buffer_reset(ring_buffer_t *ring_buffer)
{
	ring_buffer->head = 0;
	ring_buffer->tail = 0;
	ring_buffer->is_full =0;
}



