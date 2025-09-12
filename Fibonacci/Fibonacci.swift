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
        
        testRefIssues();
        
        // Create the C++ `FibonacciCalculatorCplusplus` class and invoke its `fibonacci` method.
        let cxxCalculator = FibonacciCalculatorCplusplus(printInvocation)
        return cxxCalculator.fibonacci(value - 1.0) + cxxCalculator.fibonacci(value - 2.0)
    }
    
    func testRefIssues() {
        let a = getPayloadRef(7); // : WTF.Ref<WTF.Payload, WTF.RawPtrTraits<WTF.Payload>, WTF.DefaultRefDerefTraits<WTF.Payload>>
        // let v = a.value();         // no such method available in Swift
        let b = a.ptr();
        let v = b.value();            // calling method on the Payload class
        print ("Value is \(v).")

        var a2 = Optional.some(getPayloadRef(8));
        let b2 = a2!.ptr();
        a2 = Optional.none;
        let v2 = b2.value();          // use-after-free
        print ("Value is \(v2).")
    }
}
