/*
 * Gearman PHP Extension
 *
 * Copyright (C) 2008 James M. Luedke <contact@jamesluedke.com>,
 *			Eric Day <eday@oddments.org>
 * All rights reserved.
 *
 * Use and distribution licensed under the PHP license.  See
 * the LICENSE file in this directory for full text.
 */

#ifndef __PHP_GEARMAN_TASK_H
#define __PHP_GEARMAN_TASK_H

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "zend_exceptions.h"
#include "zend_interfaces.h"

#include "php_gearman.h"
#include "php_gearman_client.h"

#include <libgearman-1.0/gearman.h>
#include <libgearman-1.0/interface/status.h>
#include <libgearman-1.0/status.h>

zend_object *gearman_task_obj_new(zend_class_entry *ce);

typedef enum {
        GEARMAN_TASK_OBJ_CREATED = (1 << 0),
} gearman_task_obj_flags_t;

typedef struct {
        gearman_return_t ret;
        gearman_task_obj_flags_t flags;
        gearman_task_st *task;
        zval zclient;
        zval zdata;
        zval zworkload;
        zend_ulong task_id;

        zend_object std;
} gearman_task_obj;

inline gearman_task_obj *gearman_task_fetch_object(zend_object *obj);
#define Z_GEARMAN_TASK_P(zv) gearman_task_fetch_object(Z_OBJ_P((zv)))

gearman_return_t _php_task_cb_fn(gearman_task_obj *task, gearman_client_obj *client, zval zcall);
void _php_task_free(gearman_task_st *task, void *context);

gearman_return_t _php_task_workload_fn(gearman_task_st *task);
gearman_return_t _php_task_created_fn(gearman_task_st *task);
gearman_return_t _php_task_data_fn(gearman_task_st *task);
gearman_return_t _php_task_warning_fn(gearman_task_st *task);
gearman_return_t _php_task_status_fn(gearman_task_st *task);
gearman_return_t _php_task_complete_fn(gearman_task_st *task);
gearman_return_t _php_task_exception_fn(gearman_task_st *task);
gearman_return_t _php_task_fail_fn(gearman_task_st *task);

#endif  /* __PHP_GEARMAN_TASK_H */
