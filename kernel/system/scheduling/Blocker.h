/*
 * Copyright (c) 2021, krishpranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

#pragma once

// includes
#include <pranaos/Time.h>
#include <libutils/Vector.h>
#include "system/node/Handle.h"
#include "system/system/System.h"

struct Task;

struct Blocker
{
private:
    JResult _result = SUCCESS;
    TimeStamp _timeout = -1;
    bool _interrupted = false;

public:
    JResult result() { return _result; }

    void timeout(TimeStamp ts) { _timeout = ts; }

    virtual ~Blocker() {}

    void unblock(Task &task)
    {
        _result = SUCCESS;
        on_unblock(task);
    }

};