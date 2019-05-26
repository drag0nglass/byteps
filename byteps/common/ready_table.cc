// Copyright 2019 ByteDance Inc. or its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =============================================================================

#include "logging.h"
#include "ready_table.h"


namespace byteps {
namespace common {


// below are methods for accessing/modifying the _ready_table
bool ReadyTable::IsKeyReady(int key) {
    std::lock_guard<std::mutex> lock(_table_mutex);
    return _ready_table[key] == (_ready_count);
}

int ReadyTable::AddReadyCount(int key) {
    std::lock_guard<std::mutex> lock(_table_mutex);
    BPS_CHECK_LT(_ready_table[key], _ready_count)
        << _ready_table[key] << ", " << (_ready_count);
    return ++_ready_table[key];
}

void ReadyTable::ClearReadyCount(int key) {
    std::lock_guard<std::mutex> lock(_table_mutex);
    _ready_table[key] = 0;
}

}
}