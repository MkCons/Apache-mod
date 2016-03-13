/* Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 
 * Apache example module.  Provide demonstrations of how modules do things.
 * It is not meant to be used in a production server.  Since it participates
 * in all of the processing phases, it could conceivable interfere with
 * the proper operation of other modules -- particularly the ones related
 * to security.
 *
 * In the interest of brevity, all functions and structures internal to
 * this module, but which may have counterparts in *real* modules, are
 * prefixed with 'x_' instead of 'example_'.
 */

#include "httpd.h"
#include "http_config.h"
#include "http_core.h"
#include "http_log.h"
#include "http_main.h"
#include "http_protocol.h"
#include "http_request.h"
#include "util_script.h"
#include "http_connection.h"

#include "apr_strings.h"

#include <stdio.h>

static void register_hooks(apr_pool_t* pool);
static int example_handler(request_rec* r);

/*
 * Declare ourselves so the configuration routines can find and know us.
 * We'll fill it in at the end of the module.
 */
module AP_MODULE_DECLARE_DATA example_module =
{
    STANDARD20_MODULE_STUFF,
    NULL,    /* per-directory config creator */
    NULL,     /* dir config merger */
    NULL, /* server config creator */
    NULL,  /* server config merger */
    NULL,                 /* command table */
    register_hooks       /* set up other request processing hooks */
};

static void register_hooks(apr_pool_t* pool) {
	ap_hook_handler(example_handler, NULL, NULL, APR_HOOK_LAST);
}

static int example_handler(request_rec* r) {
	if(!r->handler || strcmp(r->handler, "example-handler"))
		return DECLINED;

	ap_set_content_type(r, "text/html");
	ap_rprintf(r, "Hello, world!");

	return OK;
}