/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
Implements the Swift API.
*/

public struct FibonacciCalculator {
    private let printInvocation: Bool
    
    public init(printInvocation: Bool) {
        self.printInvocation = printInvocation
    }

    public func fibonacci(_ value: Double) -> Double {
        // Print the value if applicable.
        if printInvocation {
            print("[swift] fibonacci(\(value))")
        }
        
        // Handle the base case of the recursion.
        guard value > 1.0 else {
            return 1.0
        }
        
        var items: [CppRefCounted] = [];
        items.append(CppRefCounted.create(3));
        items.append(CppRefCounted.create(4));
        let cppVector = toWTFVectorAPIObject(list: items);
        printItems(cppVector);
        
        // Create the C++ `FibonacciCalculatorCplusplus` class and invoke its `fibonacci` method.
        let cxxCalculator = FibonacciCalculatorCplusplus(printInvocation)
        return cxxCalculator.fibonacci(value - 1.0) + cxxCalculator.fibonacci(value - 2.0)
    }
}

func toWTFVectorAPIObject(list: [CppRefCounted]) -> CppContainer {
    var vec = CppContainer();
    vec.reserveCapacity(list.count);
    for item in list {
        vec.append(makeSomeSmartPtr(item));
    }
    return vec
}
