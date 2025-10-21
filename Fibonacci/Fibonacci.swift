/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
Implements the Swift API.
*/

public class FibonacciCalculator {
    private let printInvocation: Bool
    
    public init(printInvocation: Bool) {
        self.printInvocation = printInvocation
    }
    
    public func hello() {
        
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
        
        // Create the C++ `FibonacciCalculatorCplusplus` class and invoke its `fibonacci` method.
        let cxxCalculator = unsafe FibonacciCalculatorCplusplus(printInvocation, OpaquePointer(Unmanaged.passUnretained(self).toOpaque()))
        return unsafe cxxCalculator.fibonacci(value - 1.0) + cxxCalculator.fibonacci(value - 2.0)
    }
}
