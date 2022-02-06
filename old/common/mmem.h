/*
 * This file is part of the Contiki operating system.
 */

/**
 * \defgroup mmem Managed memory allocator
 *
 * The managed memory allocator is a fragmentation-free memory
 * manager. It keeps the allocated memory free from fragmentation by
 * compacting the memory when blocks are freed. A program that uses
 * the managed memory module cannot be sure that allocated memory
 * stays in place. Therefore, a level of indirection is used: access
 * to allocated memory must always be done using a special macro.
 *
 * \note This module has not been heavily tested.
 * @{
 */

/**
 * \file
 *         Header file for the managed memory allocator
 *
 */

#pragma once

/*---------------------------------------------------------------------------*/
/**
 * \brief      Get a pointer to the managed memory
 * \param m    A pointer to the struct mmem
 * \return     A pointer to the memory block, or NULL if memory could
 *             not be allcated.
 * \author     Adam Dunkels
 *
 *             This macro is used to get a pointer to a memory block
 *             allocated with mmem_alloc().
 *
 * \hideinitializer
 */
#define MMEM_PTR(m) (struct mmem *)(m)->ptr
struct mmem {
  struct mmem *next;
  unsigned int size;
  void *ptr;
};

/* XXX: tagga minne med "interrupt usage", vilke gör att man är
   speciellt varsam under free(). */

int  mmem_alloc(struct mmem *m, unsigned int size);
void mmem_free(struct mmem *);
void mmem_init(void);


/** @} */
/** @} */
