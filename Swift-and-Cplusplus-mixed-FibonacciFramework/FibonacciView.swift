/*
See the LICENSE.txt file for this sample’s licensing information.

Abstract:
The SwiftUI view that shows the result of computation.
*/

import SwiftUI
import Fibonacci

func fibonacci(_ value: Double) -> Double {
    return 1;
//    return FibonacciCalculator(printInvocation: true).fibonacci(value)
}

struct FibonacciView: View {
    var body: some View {
        Text("Fibonacci(5) = \(fibonacci(5))")
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        FibonacciView()
    }
}
