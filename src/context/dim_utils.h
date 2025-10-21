// Utilidades genéricas para validación y cálculo con dimensiones multi‑dimensionales
#ifndef DIM_UTILS_H
#define DIM_UTILS_H

#include <stddef.h>

/* validar_dimensiones
 *  - n > 0, n <= 6 (límite actual)
 *  - cada dims[i] > 0
 * Retorna 1 si válido, 0 si inválido (err opcional).
 */
int validar_dimensiones(const int* dims, int n, char* err, size_t errLen);

/* validar_indices
 *  - nIdx == nDims (indexación completa)
 *  - 0 <= indices[i] < dims[i]
 */
int validar_indices(const int* dims, int nDims, const int* indices, int nIdx, char* err, size_t errLen);

/* calcular_offset_lineal (row-major)
 * offset = (((i0 * dim1) + i1) * dim2 + i2) ...
 * Si validate!=0 valida dimensiones/índices antes.
 */
int calcular_offset_lineal(const int* dims, int n, const int* indices, int nIdx, long* outOffset, int validate, char* err, size_t errLen);

#endif /* DIM_UTILS_H */
