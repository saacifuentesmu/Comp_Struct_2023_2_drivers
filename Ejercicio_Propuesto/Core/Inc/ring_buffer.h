/*
 * ring_buffer.h

 *      Author: JOHAN BEJARANO
 */

#ifndef INC_RING_BUFFER_H_
#define INC_RING_BUFFER_H_

#include <stdint.h>

typedef struct{ // es la definicion de un tipo - tipo que estamos utilizando
	uint8_t *buffer; // apuntador de memorioa  "*" es un apuntador a memoria
	uint16_t head; //cabeza - escribe un nuevo dato
	uint16_t tail; //cola - lee el dato anantiguo

	// el buffer esta lleno cuando la cabeza alcance la cola
	uint16_t capacity; //capacidad cuando el buffer esta lleno
	uint8_t is_full; //indica si el buffer esta lleno

}ring_buffer_t;


// los argumentos son las estructura que se quiere inicializar, la posicion d memoria donde queremos ubicar los datos, capacidad
void ring_buffer_init(ring_buffer_t *ring_buffer, uint8_t *buffer, uint16_t capacity);

uint8_t ring_buffer_put(ring_buffer_t *ring_buffer, uint8_t data); // Guardar datos en el buffer

uint8_t ring_buffer_get(ring_buffer_t *ring_buffer, uint8_t *data); //

uint16_t ring_buffer_size(ring_buffer_t *ring_buffer);

uint8_t ring_buffer_is_empty(ring_buffer_t *ring_buffer);

uint8_t ring_buffer_is_full(ring_buffer_t *ring_buffer);

void ring_buffer_reset(ring_buffer_t *ring_buffer);

#endif /* INC_RING_BUFFER_H_ */
