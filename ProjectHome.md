This class contains operations for

  * buffered types,
  * [ranged numbers](RangedNumber.md): cyclic numbers, clamped numbers, and ping-pong numbers,
  * [differentiable numbers](DifferentiableNumber.md), [integrable numbers](IntegrableNumber.md), [PID controllers](PIDBufferedNumber.md),
  * [response curves](ResponseCurve.md) and
  * some commonly used numerical utilities.

This library does not use the STL or exception handling, making it very portable and suitable to use with game-engine code. We used it in [MINI#37](http://www.mini37.com/) and [Rev](http://www.luma.co.za/movies/popup_movies_rev.htm). The code (in the form of a Visual Studio Solution) comes with unit tests (implemented with [Unit++](http://unitpp.sourceforge.net/)).

**Current version:** 1.6