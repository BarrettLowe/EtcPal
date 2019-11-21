/******************************************************************************
 * Copyright 2019 ETC Inc.
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
 * This file is a part of EtcPal. For more information, go to:
 * https://github.com/ETCLabs/EtcPal
 ******************************************************************************/

#include "etcpal/socket.h"

/***************************** Private macros ********************************/

/**************************** Private variables ******************************/

/*********************** Private function prototypes *************************/

// Helper functions for etcpal_poll API


// Helper functions for etcpal_setsockopt()
static int32_t join_leave_mcast_group_ipv4(etcpal_socket_t id, const struct EtcPalMreq* mreq, bool join);

/*************************** Function definitions ****************************/

static etcpal_error_t err_os_to_etcpal(uint32_t rtcserr)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_socket_init()
{
  return kEtcPalErrNotImpl;
}

void etcpal_socket_deinit()
{
}

etcpal_error_t etcpal_accept(etcpal_socket_t id, EtcPalSockAddr* address, etcpal_socket_t* conn_sock)
{
  /* TODO */
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_bind(etcpal_socket_t id, const EtcPalSockAddr* address)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_close(etcpal_socket_t id)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_connect(etcpal_socket_t id, const EtcPalSockAddr* address)
{
  /* TODO */
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_getpeername(etcpal_socket_t id, EtcPalSockAddr* address)
{
  /* TODO */
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_getsockname(etcpal_socket_t id, EtcPalSockAddr* address)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_getsockopt(etcpal_socket_t id, int level, int option_name, void* option_value, size_t* option_len)
{
  /* TODO */
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_listen(etcpal_socket_t id, int backlog)
{
  /* TODO */
  return kEtcPalErrNotImpl;
}

int etcpal_recv(etcpal_socket_t id, void* buffer, size_t length, int flags)
{
  /* TODO */
  return kEtcPalErrNotImpl;
}

int etcpal_recvfrom(etcpal_socket_t id, void* buffer, size_t length, int flags, EtcPalSockAddr* address)
{
  return 0;
}

int etcpal_send(etcpal_socket_t id, const void* message, size_t length, int flags)
{
  /* TODO */
  return kEtcPalErrNotImpl;
}

int etcpal_sendto(etcpal_socket_t id, const void* message, size_t length, int flags, const EtcPalSockAddr* dest_addr)
{
  return 0;
}

etcpal_error_t etcpal_setsockopt(etcpal_socket_t id, int level, int option_name, const void* option_value,
                                 size_t option_len)
{
  return kEtcPalErrNotImpl;
}

int32_t join_leave_mcast_group_ipv4(etcpal_socket_t id, const struct EtcPalMreq* mreq, bool join)
{
  return 0;
}

etcpal_error_t etcpal_shutdown(etcpal_socket_t id, int how)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_socket(unsigned int family, unsigned int type, etcpal_socket_t* id)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_setblocking(etcpal_socket_t id, bool blocking)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_poll_context_init(EtcPalPollContext* context)
{
  return kEtcPalErrNotImpl;
}

void etcpal_poll_context_deinit(EtcPalPollContext* context)
{
}

etcpal_error_t etcpal_poll_add_socket(EtcPalPollContext* context, etcpal_socket_t socket, etcpal_poll_events_t events,
                                      void* user_data)
{
  return kEtcPalErrNotImpl;
}

etcpal_error_t etcpal_poll_modify_socket(EtcPalPollContext* context, etcpal_socket_t socket,
                                         etcpal_poll_events_t new_events, void* new_user_data)
{
  return kEtcPalErrNotImpl;
}

void etcpal_poll_remove_socket(EtcPalPollContext* context, etcpal_socket_t socket)
{
}

etcpal_error_t etcpal_poll_wait(EtcPalPollContext* context, EtcPalPollEvent* event, int timeout_ms)
{
  return kEtcPalErrNotImpl;
}

void init_context_socket_array(EtcPalPollContext* context)
{
}

etcpal_error_t etcpal_getaddrinfo(const char* hostname, const char* service, const EtcPalAddrinfo* hints,
                                  EtcPalAddrinfo* result)
{
  return kEtcPalErrNotImpl;
}

bool etcpal_nextaddr(EtcPalAddrinfo* ai)
{
  return false;
}

void etcpal_freeaddrinfo(EtcPalAddrinfo* ai)
{
}

etcpal_error_t etcpal_getblocking(etcpal_socket_t id, bool* blocking)
{
  return kEtcPalErrNotImpl;
}
