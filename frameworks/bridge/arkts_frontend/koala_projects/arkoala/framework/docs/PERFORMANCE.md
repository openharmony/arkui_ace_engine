# Arkoala performance benchmarks

## Overview

The arkoala project lowers ets to ts and then to js by two subsequent transformations.
   * The first `ets lowering` translate `ets` to `ts with memo annotations`
   * The second `memo lowering` translates `ts with memo annotations` to a regular ts (and then js).

These `ets lowering` and `memo lowering`, among other things, cut the original code into pieces,
wrap the pieces into lambdas and the `incremental runtime` decides when to run those lambdas.

## Lifecycle of application

The lifecycle of the application is roughly the following:
We build the very first frame.
Then from frame to frame the incremental changes are applied: the `incremental runtime` executes the needed lambdas.
So we are interested in the following aspects:

   * The speed of building the first frame
   * The speed of re-building of a frame which has small changes from the previous
   * The speed of re-building of a frame which has large changes from the previous

## The frames are build from
   * ui components (such as buttons)
   * changing an attribute of a component (e.g. width of a button)

## Additional overhead

In addition to ets and memo overhead there can be just other cases which appear in their profile.

  * This benchmark reproduces a problem we have seen with parseDimension() function.
     * The benchmark [is here](https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-ui/-/blob/arkoala-bench-parse/arkoala/src/bench.ts)
     * The code has been rewritten in C++, so the priority of the issue got lower
     * Would like to throw away the C++ code, but it is of lower priority now.

### virtual machine optimizations

   * During project Koala lifetime we have encountered cases where HZ VM is slow.
      * These set of smaller benchmarks measure aspects of js machine behavior often present in the profile. In particular lambda optimizations: inlining, getting rid of closure object etc
         * https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-ui/-/blob/master/koala-demo/src/components/JSBenchmark.ts

Please note that parts of performance benchmark scripts and tools were moved to the [closed repository](https://rnd-gitlab-msc.huawei.com/rus-os-team/koala-ui/koala-closed/-/merge_requests/2).