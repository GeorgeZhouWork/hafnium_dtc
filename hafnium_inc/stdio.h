/*
 * Copyright 2020 The Hafnium Authors.
 *
 * Use of this source code is governed by a BSD-style license that can be found
 * in the LICENSE file of the main Hafnium repository or at
 * https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

#include "hf/check.h"
#include "hf/dlog.h"

#define printf  dlog
#define off_t   uint64_t
