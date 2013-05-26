#ifndef GOSU_MACUTILITY_HPP
#define GOSU_MACUTILITY_HPP

#include <Gosu/Platform.hpp>

#import <CoreFoundation/CoreFoundation.h>

#ifndef GOSU_IS_IPHONE
#import <ApplicationServices/ApplicationServices.h>

// Not defined on 10.4 Tiger SDK which Gosu uses.
#if __LP64__ || NS_BUILD_32_LIKE_64
typedef long NSInteger;
typedef unsigned long NSUInteger;
#else
typedef int NSInteger;
typedef unsigned int NSUInteger;
#endif
#endif

#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <stdexcept>

namespace Gosu
{
    inline void throwOSError(OSStatus status, unsigned line)
    {
        std::ostringstream str;
        #ifdef GOSU_IS_IPHONE
        str << "Error on line " << line << " (Code " << status << ")";
        #else
        str << "Error on line " << line << " (Code " << status << "): "
            << GetMacOSStatusErrorString(status)
            << " (" << GetMacOSStatusCommentString(status) << ")";
        #endif
        throw std::runtime_error(str.str());
    }
    
    #define CHECK_OS(status) if (!(status)) {} else Gosu::throwOSError(status, __LINE__)
}

#ifdef __OBJC__
#import <objc/objc.h>
#import <stdexcept>
namespace Gosu
{
    template<typename T>
    class ObjRef
    {
        ObjRef(const ObjRef&);
        ObjRef& operator=(const ObjRef&);
        
        T* ptr;
    public:
        ObjRef(T* ptr = nil)
        : ptr(ptr) 
        {
        }
        
        ~ObjRef() 
        {
            if (ptr)
                [ptr release];
        }
        
        void reset(T* newPtr = nil)
        { 
            if (ptr)
                [ptr release]; 
            ptr = newPtr;
        }
        
        T* get() const 
        {
            return ptr; 
        }
        
        T* obj() const
        {
            if (!ptr)
                throw std::logic_error("Tried dereferencing nil");
            return ptr;
        }
    };
}
#endif

namespace Gosu
{
    template<typename CFRefType = CFTypeRef>
    class CFRef
    {
        CFRef(const CFRef&);
        CFRef& operator=(const CFRef&);
        
        CFRefType ref;
        
    public:
        CFRef(CFRefType ref)
        :   ref(ref)
        {
        }
        
        CFRef()
        {
            if (ref)
                CFRelease(ref);
        }
        
        CFRefType get()
        {
            return ref;
        }
        
        CFRefType obj()
        {
            if (!ref)
                throw std::logic_error("CF reference invalid (null)");
            return ref;
        }
    };
}

#endif
