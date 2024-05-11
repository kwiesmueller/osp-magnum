/**
 * Open Space Program
 * Copyright © 2019-2024 Open Space Program Project
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

#include "chunk_utils.h"


namespace planeta
{

ChunkFillSubdivLUT make_chunk_vrtx_subdiv_lut(uint8_t const subdivLevel)
{
    ChunkFillSubdivLUT out;

    out.m_edgeVrtxCount = 1u << subdivLevel;
    out.m_fillVrtxCount = (out.m_edgeVrtxCount-2) * (out.m_edgeVrtxCount-1) / 2;

    out.m_data.reserve(out.m_fillVrtxCount);

    // Calculate LUT, this fills m_data
    out.fill_tri_recurse({0,                   0              },
                         {0,                   out.m_edgeVrtxCount},
                         {out.m_edgeVrtxCount, out.m_edgeVrtxCount},
                         subdivLevel);

    return out;

    // Future optimization:
    // m_data can be sorted in a way that slightly improves cache locality
    // by accessing to fill vertices in a more sequential order.
}

void ChunkFillSubdivLUT::subdiv_line_recurse(
        Vector2us const a, Vector2us const b, uint8_t const level)
{
    Vector2us const mid = (a + b) / 2;

    ChunkLocalSharedId const out = ChunkLocalSharedId(xy_to_triangular(mid.x() - 1, mid.y() - 2));

    m_data.emplace_back(ToSubdiv{id_at(a), id_at(b), out});

    if (level > 1)
    {
        subdiv_line_recurse(a, mid, level - 1);
        subdiv_line_recurse(mid, b, level - 1);
    }

}

void ChunkFillSubdivLUT::fill_tri_recurse(
        Vector2us const top, Vector2us const lft, Vector2us const rte, uint8_t const level)
{
    // calculate midpoints
    std::array<Vector2us, 3> const mid
    {{
        (top + lft) / 2,
        (lft + rte) / 2,
        (rte + top) / 2
    }};

    uint8_t const levelNext = level - 1;

    // make lines between them
    if (level > 1)
    {
        subdiv_line_recurse(mid[0], mid[1], levelNext);
        subdiv_line_recurse(mid[1], mid[2], levelNext);
        subdiv_line_recurse(mid[2], mid[0], levelNext);
    }

    if (level > 2)
    {
        fill_tri_recurse(   top, mid[0], mid[2], levelNext); // top
        fill_tri_recurse(mid[0],    lft, mid[1], levelNext); // left
        fill_tri_recurse(mid[1], mid[2], mid[0], levelNext); // center
        fill_tri_recurse(mid[2], mid[1],    rte, levelNext); // right
    }
}

} // namespace planeta
