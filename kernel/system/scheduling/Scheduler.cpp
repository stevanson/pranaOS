/*
 * Copyright (c) 2021, krishpranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

// incldues
#include <libutils/List.h>
#include "archs/Arch.h"
#include "system/interrupts/Interupts.h"
#include "system/scheduling/Scheduler.h"
#include "system/system/System.h"

static bool scheduler_context_switch = false;
static int scheduler_record[SCHEDULER_RECORD_COUNT] = {};

static Task *running = nullptr;
static Task *idle = nullptr;

static Utils::List<Task *> *blocked_tasks;
static Utils::List<Task *> *running_tasks;

void scheduler_initialize()
{
    blocked_tasks = new Utils::List<Task *>();
    running_tasks = new Utils::List<Task *>();
}

void scheduler_did_create_idle_task(Task *task)
{
    idle = task;
}

void scheduler_did_create_running_task(Task *task)
{
    running = task;
}

void scheduler_did_change_task_state(Task *task, TaskState oldstate, TaskState newstate)
{
    ASSERT_INTERRUPTS_RETAINED();

    if (oldstate != newstate)
    {
        if (oldstate == TASK_STATE_RUNNING)
        {
            running_tasks->remove(task);
        }

        if (oldstate == TASK_STATE_BLOCKED)
        {
            blocked_tasks->remove(task);
        }

        if (newstate == TASK_STATE_BLOCKED)
        {
            blocked_tasks->push_back(task);
        }

        if (newstate == TASK_STATE_RUNNING)
        {
            running_tasks->push_back(task);
        }
    }
}