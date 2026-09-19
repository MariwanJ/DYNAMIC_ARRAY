//
// MIT License
//
// Copyright (c) 2026
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Author :Mariwan Jalal
//

#include <stdio.h>
#include <stdlib.h>
#include <dynamic.h>

//  An example showing how you can use the dynamic array.
int main(void)
{
    dynamicA D;

    INIT_DYNAMIC_ARRAY(&D);
    char str[] = "This is a string to be saved";
    /* Stack-allocated arrays */
    PUSH_ITEM(&D, CREATE_ELEMENT(str, TYPE_CHAR, ARRAY_LENGTH(str)));
    for (size_t j = 0; j < D.count; ++j)
    {
        PRINT_ITEM(&D.items[j]);
    }
    /* Free memory owned by the dynamic array */
    FREE_DYNAMIC_ARRAY(&D);
    return 0;
}