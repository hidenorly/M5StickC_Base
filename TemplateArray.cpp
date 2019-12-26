/* 
 Copyright (C) 2016,2018,2019 hidenorly

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/

#include "base.h"
#include "TemplateArray.h"

template <typename T>
TemplateArray<T>::TemplateArray(int nMaxArray)
{
  AutoDisableInterrupt lock();
  mMaxArray=nMaxArray;
  mpContents = new T*[mMaxArray];
  for(int i=0; i<mMaxArray; i++){
    mpContents[i]=NULL;
  }
}

template <typename T>
TemplateArray<T>::~TemplateArray()
{
  AutoDisableInterrupt lock();
  for(int i=0; i<mMaxArray; i++){
    delete mpContents[i];
    mpContents[i]=NULL;
  }
  delete mpContents;
  mpContents = NULL;
}

template <typename T>
void TemplateArray<T>::add(T* pContent)
{
  AutoDisableInterrupt lock();
  for(int i=0; i<mMaxArray; i++){
    if( NULL == mpContents[i] ){
      mpContents[i] = pContent;
      return;
    }
  }
}

template <typename T>
void TemplateArray<T>::remove(T* pContent)
{
  AutoDisableInterrupt lock();
  for(int i=0; i<mMaxArray; i++){
    if( pContent == mpContents[i] ){
      delete pContent;
      mpContents[i] = NULL;
    }
  }
}

template <typename T>
T* TemplateArray<T>::getPtr(int i)
{
  AutoDisableInterrupt lock();
  if( (i<0) || (i>mMaxArray) ) return NULL;
  return mpContents[i];
}
     
template <typename T>
int TemplateArray<T>::size(void)
{
  return mMaxArray;
}

// TODO: I'm not sure why but I cannot instanciate template class TemplateArray<LooperThreadTicker>; in LooperThreadTicker.cpp. But here is Ok...
#include "LooperThreadTicker.h"
template class TemplateArray<LooperThreadTicker>;
