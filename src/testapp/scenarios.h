/**
 * Open Space Program
 * Copyright © 2019-2021 Open Space Program Project
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include "identifiers.h"
#include "testapp.h"

// IWYU pragma: begin_exports
#include <osp/tasks/top_utils.h>
// IWYU pragma: end_exports

#include <unordered_map>

namespace testapp
{

namespace scenes
{
    using enum EStgOptn;
    using enum EStgCont;
    using enum EStgIntr;
    using enum EStgRevd;
    using enum EStgEvnt;
    using enum EStgFBO;
    using enum EStgLink;
}

struct MainLoopControl
{
    bool doUpdate;
    bool doSync;
    bool doResync;
    bool doRender;
};

struct ScenarioOption
{
    std::string_view m_description;
    SceneSetupFunc_t m_setup;
};

using ScenarioMap_t = std::unordered_map<std::string_view, ScenarioOption>;

ScenarioMap_t const& scenarios();

} // namespace testapp
