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

        let nums: [Int32] = [0, 1];
        takeSpan(nums.span);

        let bobbins = "hello";
        takeSpanChar(bobbins.utf8CString.span);
        takeSpanConstChar(bobbins.utf8CString.span);

        // Create the C++ `FibonacciCalculatorCplusplus` class and invoke its `fibonacci` method.
        let cxxCalculator = FibonacciCalculatorCplusplus(printInvocation)
        return cxxCalculator.fibonacci(value - 1.0) + cxxCalculator.fibonacci(value - 2.0)
    }
}
