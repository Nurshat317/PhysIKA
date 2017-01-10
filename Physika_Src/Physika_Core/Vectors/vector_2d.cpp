/*
 * @file vector_2d.cpp 
 * @brief 2d vector.
 * @author Fei Zhu, Wei Chen
 * 
 * This file is part of Physika, a versatile physics simulation library.
 * Copyright (C) 2013- Physika Group.
 *
 * This Source Code Form is subject to the terms of the GNU General Public License v2.0. 
 * If a copy of the GPL was not distributed with this file, you can obtain one at:
 * http://www.gnu.org/licenses/gpl-2.0.html
 *
 */

#include <limits>
#include <cstdlib>
#include <iostream>
#include "Physika_Core/Utilities/physika_exception.h"
#include "Physika_Core/Utilities/math_utilities.h"
#include "Physika_Core/Matrices/matrix_2x2.h"
#include "Physika_Core/Vectors/vector_2d.h"

namespace Physika{

template <typename Scalar>
Vector<Scalar,2>::Vector()
    :Vector(0) //delegating ctor
{
}

template <typename Scalar>
Vector<Scalar, 2>::Vector(Scalar x)
    :Vector(x, x) //delegating ctor
{

}

template <typename Scalar>
Vector<Scalar,2>::Vector(Scalar x, Scalar y)
{
#ifdef PHYSIKA_USE_EIGEN_VECTOR
    eigen_vector_2x_(0)=x;
    eigen_vector_2x_(1)=y;
#elif defined(PHYSIKA_USE_BUILT_IN_VECTOR)
    data_[0]=x;
    data_[1]=y;
#endif
}


template <typename Scalar>
Scalar& Vector<Scalar,2>::operator[] (unsigned int idx)
{
    return const_cast<Scalar &>(static_cast<const Vector<Scalar, 2> &>(*this)[idx]);
}

template <typename Scalar>
const Scalar& Vector<Scalar,2>::operator[] (unsigned int idx) const
{
    if(idx>=2)
        throw PhysikaException("Vector index out of range!");
#ifdef PHYSIKA_USE_EIGEN_VECTOR
    return eigen_vector_2x_(idx);
#elif defined(PHYSIKA_USE_BUILT_IN_VECTOR)
    return data_[idx];
#endif
}

template <typename Scalar>
const Vector<Scalar,2> Vector<Scalar,2>::operator+ (const Vector<Scalar,2> &vec2) const
{
    return Vector<Scalar, 2>(*this) += vec2;
}

template <typename Scalar>
Vector<Scalar,2>& Vector<Scalar,2>::operator+= (const Vector<Scalar,2> &vec2)
{
    for(unsigned int i = 0; i < 2; ++i)
        (*this)[i] += vec2[i];
    return *this;
}

template <typename Scalar>
const Vector<Scalar,2> Vector<Scalar,2>::operator- (const Vector<Scalar,2> &vec2) const
{
    return Vector<Scalar, 2>(*this) -= vec2;
}

template <typename Scalar>
Vector<Scalar,2>& Vector<Scalar,2>::operator-= (const Vector<Scalar,2> &vec2)
{
    for(unsigned int i = 0; i < 2; ++i)
        (*this)[i] -= vec2[i];
    return *this;
}

template <typename Scalar>
bool Vector<Scalar,2>::operator== (const Vector<Scalar,2> &vec2) const
{
    for(unsigned int i = 0; i < 2; ++i)
    {
        if(is_floating_point<Scalar>::value)
        {
            if(isEqual((*this)[i],vec2[i])==false)
                return false;
        }
        else
        {
            if((*this)[i] != vec2[i])
                return false;
        }
    }
    return true;
}

template <typename Scalar>
bool Vector<Scalar,2>::operator!= (const Vector<Scalar,2> &vec2) const
{
    return !((*this)==vec2);
}

template <typename Scalar>
const Vector<Scalar, 2> Vector<Scalar, 2>::operator+(Scalar value) const
{
    return Vector<Scalar, 2>(*this) += value;
}


template <typename Scalar>
Vector<Scalar, 2>& Vector<Scalar, 2>::operator+= (Scalar value)
{
    for (unsigned int i = 0; i < 2; ++i)
        (*this)[i] += value;
    return *this;
}

template <typename Scalar>
const Vector<Scalar, 2> Vector<Scalar, 2>::operator-(Scalar value) const
{
    return Vector<Scalar, 2>(*this) -= value;
}

template <typename Scalar>
Vector<Scalar, 2>& Vector<Scalar, 2>::operator-= (Scalar value)
{
    for (unsigned int i = 0; i < 2; ++i)
        (*this)[i] -= value;
    return *this;
}

template <typename Scalar>
const Vector<Scalar,2> Vector<Scalar,2>::operator* (Scalar scale) const
{
    return Vector<Scalar, 2>(*this) *= scale;
}

template <typename Scalar>
Vector<Scalar,2>& Vector<Scalar,2>::operator*= (Scalar scale)
{
    for(unsigned int i = 0; i < 2; ++i)
        (*this)[i] *= scale;
    return *this;
}

template <typename Scalar>
const Vector<Scalar,2> Vector<Scalar,2>::operator/ (Scalar scale) const
{
    return Vector<Scalar, 2>(*this) /= scale;
}

template <typename Scalar>
Vector<Scalar,2>& Vector<Scalar,2>::operator/= (Scalar scale)
{
    if(abs(scale) <= std::numeric_limits<Scalar>::epsilon())
        throw PhysikaException("Vector Divide by zero error!");
    for(unsigned int i = 0; i < 2; ++i)
        (*this)[i] /= scale;
    return *this;
}

template <typename Scalar>
const Vector<Scalar, 2> Vector<Scalar, 2>::operator-(void) const
{
    return Vector<Scalar, 2>(-(*this)[0], -(*this)[1]);
}

template <typename Scalar>
Scalar Vector<Scalar,2>::norm() const
{
    Scalar result = (*this)[0]*(*this)[0] + (*this)[1]*(*this)[1];
    result = static_cast<Scalar>(sqrt(result));
    return result;
}

template <typename Scalar>
Scalar Vector<Scalar,2>::normSquared() const
{
    Scalar result = (*this)[0]*(*this)[0] + (*this)[1]*(*this)[1];
    return result;
}

template <typename Scalar>
Vector<Scalar,2>& Vector<Scalar,2>::normalize()
{
    Scalar norm = (*this).norm();
    bool nonzero_norm = norm > std::numeric_limits<Scalar>::epsilon();
    if(nonzero_norm)
    {
        for(int i = 0; i < 2; ++i)
            (*this)[i] /= norm;
    }
    return *this;
}

template <typename Scalar>
Scalar Vector<Scalar,2>::cross(const Vector<Scalar,2>& vec2) const
{
    return (*this)[0]*vec2[1] - (*this)[1]*vec2[0];
}

template <typename Scalar>
Scalar Vector<Scalar,2>::dot(const Vector<Scalar,2>& vec2) const
{
    return (*this)[0]*vec2[0] + (*this)[1]*vec2[1];
}

template <typename Scalar>
const SquareMatrix<Scalar,2> Vector<Scalar,2>::outerProduct(const Vector<Scalar,2> &vec2) const
{
    SquareMatrix<Scalar,2> result;
    for(unsigned int i = 0; i < 2; ++i)
        for(unsigned int j = 0; j < 2; ++j)
            result(i,j) = (*this)[i]*vec2[j];
    return result;
}

//explicit instantiation of template so that it could be compiled into a lib
template class Vector<unsigned char,2>;
template class Vector<unsigned short,2>;
template class Vector<unsigned int,2>;
template class Vector<unsigned long,2>;
template class Vector<unsigned long long,2>;
template class Vector<signed char,2>;
template class Vector<short,2>;
template class Vector<int,2>;
template class Vector<long,2>;
template class Vector<long long,2>;
template class Vector<float,2>;
template class Vector<double,2>;
template class Vector<long double,2>;

} //end of namespace Physika
