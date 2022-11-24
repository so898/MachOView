//
//  objc_headers.h
//  machoview
//
//  Created by Bill Cheng on 2022/11/25.
//

#ifndef objc_headers_h
#define objc_headers_h
#import <Foundation/Foundation.h>
#include <cstdint>
#include <atomic>
#include <type_traits>

typedef uintptr_t protocol_ref_t;  // protocol_t *, but unremapped

struct objc_class_rw_t {
    uint32_t flags;
    uint16_t witness;
};

// data pointer
#define FAST_DATA_MASK          0x00007ffffffffff8UL
// class is a Swift class from the pre-stable Swift ABI
#define FAST_IS_SWIFT_LEGACY    (1UL<<0)
// class is a Swift class from the stable Swift ABI
#define FAST_IS_SWIFT_STABLE    (1UL<<1)

struct objc_class_t {
    uint64_t metaClass;
    uint64_t superClass;
    uint64_t cache;
    uint64_t vtable;
    uint64_t bits;
    
    const uint64_t data() const {
        return (uint64_t)(bits & FAST_DATA_MASK);
    }
    
    const bool isAnySwift() const {
        return isSwiftStable() || isSwiftLegacy();
    }
    
    const bool isSwiftStable() const {
        return getBit(FAST_IS_SWIFT_STABLE);
    }
    
    const bool isSwiftLegacy() const {
        return getBit(FAST_IS_SWIFT_LEGACY);
    }
private:
    const bool getBit(uintptr_t bit) const
    {
        return bits & bit;
    }
};

struct swift_class_t : objc_class_t {
    uint32_t flags;
    uint32_t instanceAddressOffset;
    uint32_t instanceSize;
    uint16_t instanceAlignMask;
    uint16_t reserved;
    
    uint32_t classSize;
    uint32_t classAddressOffset;
    void *description;
    // ...
    
    const void *baseAddress() {
        return (void *)((uint8_t *)this - classAddressOffset);
    }
};

struct objc_method_t {
    uint64_t name;
    uint64_t types;
    uint64_t imp;
};

struct objc_method_list_t {
    uint32_t entsizeAndFlags;
    uint32_t count;
    
    const uint32_t entsize() const {
        return entsizeAndFlags & ~0xffff0003;
    }
    const uint32_t flags() const {
        return entsizeAndFlags & 0xffff0003;
    }
};

struct objc_protocol_list_t {
    // count is pointer-sized by accident.
    uintptr_t count;
    protocol_ref_t list[0]; // variable-size
};

struct objc_category_t {
    uint64_t name; //const char *
    uint64_t cls; // classref_t
    uint64_t instanceMethods;// objc_method_list_t *
    uint64_t classMethods;// objc_method_list_t *
    uint64_t protocols; // struct objc_protocol_list_t *
    uint64_t instanceProperties; // struct objc_protocol_list_t *
    // Fields below this point are not always present on disk.
    uint64_t _classProperties; // struct objc_protocol_list_t *
};

#endif /* objc_headers_h */
