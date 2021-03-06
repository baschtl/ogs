/**
 * \copyright
 * Copyright (c) 2012-2015, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#ifndef ASSEMBLERLIB_SERIALDENSESETUP_H_
#define ASSEMBLERLIB_SERIALDENSESETUP_H_


#include "AssemblerLib/GlobalSetup.h"

#include "AssemblerLib/SerialDenseVectorMatrixBuilder.h"
#include "AssemblerLib/SerialExecutor.h"
#include "AssemblerLib/SerialExecutor.h"
#include "MathLib/LinAlg/Solvers/GaussAlgorithm.h"

namespace AssemblerLib
{

/// Using GlobalDenseMatrix and DenseVector for global entities and serial
/// global assembly loop.
typedef GlobalSetup<
        AssemblerLib::SerialDenseVectorMatrixBuilder,
        AssemblerLib::SerialExecutor,
        MathLib::GaussAlgorithm<
            typename AssemblerLib::SerialDenseVectorMatrixBuilder::MatrixType,
            typename AssemblerLib::SerialDenseVectorMatrixBuilder::VectorType>
        >
    SerialDenseSetup;

}   // namespace AssemblerLib

#endif  // ASSEMBLERLIB_SERIALDENSESETUP_H_
