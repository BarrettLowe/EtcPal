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
 * This file is a part of lwpa. For more information, go to:
 * https://github.com/ETCLabs/lwpa
 ******************************************************************************/

/* lwpa_mock/socket.h: Mock functions for the lwpa_socket API. */
#ifndef _LWPA_MOCK_SOCKET_H_
#define _LWPA_MOCK_SOCKET_H_

#include "lwpa/socket.h"
#include "lwpa_mock/fff.h"

// We don't mock:
// lwpa_inet_pton()
// lwpa_inet_ntop()
// sockaddr_plat_to_lwpa()
// sockaddr_lwpa_to_plat()

#ifdef __cplusplus
extern "C" {
#endif

DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_socket_init, void *);
DECLARE_FAKE_VOID_FUNC(lwpa_socket_deinit);

DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_accept, lwpa_socket_t, LwpaSockaddr *, lwpa_socket_t *);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_bind, lwpa_socket_t, const LwpaSockaddr *);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_close, lwpa_socket_t);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_connect, lwpa_socket_t, const LwpaSockaddr *);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_getpeername, lwpa_socket_t, LwpaSockaddr *);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_getsockname, lwpa_socket_t, LwpaSockaddr *);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_getsockopt, lwpa_socket_t, int, int, void *, size_t *);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_listen, lwpa_socket_t, int);
DECLARE_FAKE_VALUE_FUNC(int, lwpa_recv, lwpa_socket_t, void *, size_t, int);
DECLARE_FAKE_VALUE_FUNC(int, lwpa_recvfrom, lwpa_socket_t, void *, size_t, int, LwpaSockaddr *);
DECLARE_FAKE_VALUE_FUNC(int, lwpa_send, lwpa_socket_t, const void *, size_t, int);
DECLARE_FAKE_VALUE_FUNC(int, lwpa_sendto, lwpa_socket_t, const void *, size_t, int, const LwpaSockaddr *);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_setsockopt, lwpa_socket_t, int, int, const void *, size_t);
DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_shutdown, lwpa_socket_t, int);
DECLARE_FAKE_VALUE_FUNC(lwpa_socket_t, lwpa_socket, unsigned int, unsigned int);

DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_setblocking, lwpa_socket_t, bool);

DECLARE_FAKE_VALUE_FUNC(int, lwpa_poll, LwpaPollfd *, size_t, int);

DECLARE_FAKE_VALUE_FUNC(lwpa_error_t, lwpa_getaddrinfo, const char *, const char *, const LwpaAddrinfo *,
                        LwpaAddrinfo *);
DECLARE_FAKE_VALUE_FUNC(bool, lwpa_nextaddr, LwpaAddrinfo *);
DECLARE_FAKE_VOID_FUNC(lwpa_freeaddrinfo, LwpaAddrinfo *);

#ifdef __cplusplus
}
#endif

#endif /* _LWPA_MOCK_SOCKET_H_ */
