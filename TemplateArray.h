/* 
 Copyright (C) 2016 hidenorly

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

#ifndef __TEMPLATE_ARRAY_H__
#define __TEMPLATE_ARRAY_H__

template <typename T>
class TemplateArray
{
  public:
    TemplateArray(int nMaxArray=10);
    ~TemplateArray();
    void add(T* pTicker);
    void remove(T* pTicker);
    T* getPtr(int i);
    int size(void);

  protected:
    T** mpContents;
    int mMaxArray;
};

#endif // __TEMPLATE_ARRAY_H__