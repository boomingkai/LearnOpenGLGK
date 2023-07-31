/*
-----------------------------------------------------------------------------
This source file is part of CHAOS
    (Chaos Game Engine)
For the latest info, see http://www.boominggames.com/

Copyright (c) 2000-2005 The CHAOS Team

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "client/precompiled/chaos_client_stable_headers.h"
#include "client/animation/chaos_pose.h"
#include "client/render/RHI/chaos_render_hardware_interface.h"

namespace Chaos {
    //---------------------------------------------------------------------
    Pose::Pose(UShort target, const String& name)
        : mTarget(target), mName(name)
    {
    }
    //---------------------------------------------------------------------
    Pose::~Pose()
    {
    }
    //---------------------------------------------------------------------
    void Pose::addVertex(size_t index, const Vector3& offset)
    {
        if (!mNormalsMap.isEmpty())
            LOG_ERROR("Pose::addVertex", "Inconsistent calls to addVertex, must include normals always or never");

        if(offset.squaredLength() < 1e-6f)
        {
            return;
        }

        mVertexOffsetMap[index] = offset;
    }
    //---------------------------------------------------------------------
    void Pose::addVertex(size_t index, const Vector3& offset, const Vector3& normal)
    {
        if (!mVertexOffsetMap.isEmpty() && mNormalsMap.isEmpty())
            LOG_ERROR("Pose::addVertex", "Inconsistent calls to addVertex, must include normals always or never");

        if(offset.squaredLength() < 1e-6f && normal.squaredLength() < 1e-6f)
        {
            return;
        }

        mVertexOffsetMap[index] = offset;
        mNormalsMap[index] = normal;
    }
    //---------------------------------------------------------------------
    void Pose::removeVertex(size_t index)
    {
        VertexOffsetMap::iterator i = mVertexOffsetMap.find(index);
        if (i != mVertexOffsetMap.end())
        {
            mVertexOffsetMap.erase(i);
        }
        NormalsMap::iterator j = mNormalsMap.find(index);
        if (j != mNormalsMap.end())
        {
            mNormalsMap.erase(j);
        }
    }
    //---------------------------------------------------------------------
    void Pose::clearVertices(void)
    {
        mVertexOffsetMap.clear();
        mNormalsMap.clear();
    }
   
    //---------------------------------------------------------------------
    Pose* Pose::clone(void) const
    {
        Pose* newPose = CHAOS_NEW_T(Pose)(mTarget, mName);
        newPose->mVertexOffsetMap = mVertexOffsetMap;
        newPose->mNormalsMap = mNormalsMap;
        // Allow buffer to recreate itself, contents may change anyway
        return newPose;
    }

}
