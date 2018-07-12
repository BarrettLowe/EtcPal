/******************************************************************************
 * Copyright 2018 ETC Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************
 * This file is a part of lwpa. For more information, go to:
 * https://github.com/ETCLabs/lwpa
 ******************************************************************************/

/* pdu.h: Functions to parse and pack a generic PDU as defined in ANSI
 * E1.17. */
#ifndef _LWPA_PDU_H_
#define _LWPA_PDU_H_

#include <stddef.h>
#include "lwpa_int.h"
#include "lwpa_bool.h"

/*! \defgroup lwpa_pdu lwpa_pdu
 *  \ingroup lwpa
 *  \brief Parse or pack a generic PDU or PDU block.
 *
 *  \#include "lwpa_pdu.h"
 *
 *  @{
 */

/*! \name Get the inheritance and length bits in a PDU Flags & Length segment.
 *  The first byte of each PDU contains a flags field which indicates the
 *  inheritance properties of that PDU. For more information, see ANSI E1.17,
 *  ACN Architecture, s. 2.4.
 *  @{
 */
/*! Determine whether the L flag is set in a PDU flags field.
 *  \param flags_byte The first byte of the PDU.
 *  \return true (the L flag is set) or false (the L flags is not set). */
#define l_flag_set(flags_byte) ((bool)(flags_byte & 0x80))
/*! Determine whether the V flag is set in a PDU flags field.
 *  \param flags_byte The first byte of the PDU.
 *  \return true (the V flag is set) or false (the V flag is not set). */
#define v_flag_set(flags_byte) ((bool)(flags_byte & 0x40))
/*! Determine whether the H flag is set in a PDU flags field.
 *  \param flags_byte The first byte of the PDU.
 *  \return true (the H flag is set) or false (the H flag is not set). */
#define h_flag_set(flags_byte) ((bool)(flags_byte & 0x20))
/*! Determine whether the D flag is set in a PDU flags field.
 *  \param flags_byte The first byte of the PDU.
 *  \return true (the D flag is set) or false (the D flag is not set). */
#define d_flag_set(flags_byte) ((bool)(flags_byte & 0x10))
/*!@}*/

/*! Get the length from the Length field of a PDU.
 *  \param pdu_buf Pointer to the start of the PDU buffer.
 *  \return The length of the PDU. */
#define pdu_length(pdu_buf)                                                                           \
  ((uint32_t)(l_flag_set(pdu_buf[0]) ? (((pdu_buf[0] & 0x0f) << 16) | (pdu_buf[1] << 8) | pdu_buf[2]) \
                                     : (((pdu_buf[0] & 0x0f) << 8) | pdu_buf[1])))

/*! \name Set the inheritance and length bits in a PDU Flags & Length segment.
 *  The first byte of each PDU contains a flags field which indicates the
 *  inheritance properties of that PDU. For more information, see ANSI E1.17,
 *  ACN Architecture, s. 2.4.
 *  @{
 */
/*! Set the L flag in a PDU flags field.
 *  \param flags_byte The first byte of the PDU. */
#define set_l_flag(flags_byte) (flags_byte |= 0x80)
/*! Set the V flag in a PDU flags field.
 *  \param flags_byte The first byte of the PDU. */
#define set_v_flag(flags_byte) (flags_byte |= 0x40)
/*! Set the H flag in a PDU flags field.
 *  \param flags_byte The first byte of the PDU. */
#define set_h_flag(flags_byte) (flags_byte |= 0x20)
/*! Set the D flag in a PDU flags field.
 *  \param flags_byte The first byte of the PDU. */
#define set_d_flag(flags_byte) (flags_byte |= 0x10)
/*!@}*/

/*! Fill in the Length field of a PDU which has a length less than 4096. The L
 *  flag of this PDU must be set to 0.
 *  \param pdu_buf Pointer to the start of the PDU buffer.
 *  \param length Length of this PDU.
 */
#define pdu_pack_normal_len(pdu_buf, length)                           \
  do                                                                   \
  {                                                                    \
    (pdu_buf)[0] = (((pdu_buf)[0] & 0xf0) | (((length) >> 8) & 0x0f)); \
    (pdu_buf)[1] = (length)&0xff;                                      \
  } while (0)

/*! Fill in the Length field of a PDU which has a length 4096 or greater. The
 *  L flag of this PDU must be set to 1.
 *  \param pdu_buf Pointer to the start of the PDU buffer.
 *  \param length Length of this PDU.
 */
#define pdu_pack_ext_len(pdu_buf, length)                               \
  do                                                                    \
  {                                                                     \
    (pdu_buf)[0] = (((pdu_buf)[0] & 0xf0) | (((length) >> 16) & 0x0f)); \
    (pdu_buf)[1] = (((length) >> 8) & 0xff);                            \
    (pdu_buf)[2] = (length)&0xff;                                       \
  } while (0)

/*! Holds state data used when parsing multiple PDUs in a PDU block. */
typedef struct LwpaPdu
{
  const uint8_t *pvector;
  const uint8_t *pheader;
  const uint8_t *pdata;
  size_t datalen;
  const uint8_t *pnextpdu;
} LwpaPdu;

/*! Default LwpaPdu initializer values; must be used to intialize a struct
 *  pdu when parsing the first PDU in a block. */
#define PDU_INIT              \
  {                           \
    NULL, NULL, NULL, 0, NULL \
  }

/*! An alternative to #PDU_INIT which can be used on an existing LwpaPdu to
 *  re-initialize its values.
 *  \param pduptr Pointer to LwpaPdu to initialize. */
#define init_pdu(pduptr)       \
  do                           \
  {                            \
    (pduptr)->pvector = NULL;  \
    (pduptr)->pheader = NULL;  \
    (pduptr)->pdata = NULL;    \
    (pduptr)->datalen = 0;     \
    (pduptr)->pnextpdu = NULL; \
  } while (0)

/*! Contains specific PDU info used by the generic helper parse_pdu(). */
typedef struct LwpaPduConstraints
{
  size_t vector_size; /*!< The size of the Vector segment of this PDU. */
  size_t header_size; /*!< The size of the Header segment of this PDU. */
} LwpaPduConstraints;

#ifdef __cplusplus
extern "C" {
#endif

bool parse_pdu(const uint8_t *buf, size_t buflen, const LwpaPduConstraints *constraints, LwpaPdu *pdu);

#ifdef __cplusplus
}
#endif

/*!@}*/

#endif /* _LWPA_PDU_H_ */
