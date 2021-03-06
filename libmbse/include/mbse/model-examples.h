/*+-------------------------------------------------------------------------+
  |            Multi Body State Estimation (mbse) C++ library               |
  |                                                                         |
  | Copyright (C) 2014-2020 University of Almeria                           |
  | Copyright (C) 2020 University of Salento                                |
  | See README for list of authors and papers                               |
  | Distributed under 3-clause BSD license                                  |
  |  See: <https://opensource.org/licenses/BSD-3-Clause>                    |
  +-------------------------------------------------------------------------+ */

#pragma once

#include <mbse/CModelDefinition.h>

namespace mbse
{
/** Builds a model of a NX x NY grid of four bar mechanisms.
 * \image docs/parameterized_fourbar.png
 */
CModelDefinition buildParameterizedMBS(
	const size_t nx, const size_t ny, const double NOISE_LEN = 0);

/** Builds a model of an N parts pendulum.
 * \todo Add picture!
 */
CModelDefinition buildLongStringMBS(
	const size_t N, double segmentLength = 0.5,
	double segmentMassPerMeter = 1.0);

/** Builds a model of an 4-bar mechanism.
 * \todo Add picture!
 * Degrees of freedom in q=[x1 y1 x2 y2]^T
 *
 */
CModelDefinition buildFourBarsMBS();

/** Builds a model of a slider crank mechanism.
 * \todo Add picture!
 * Degrees of freedom in q=[..]^T
 */
CModelDefinition buildSliderCrankMBS();

CModelDefinition buildFollowerMBS();

CModelDefinition buildTwoSliderBlocks();

}  // namespace mbse
