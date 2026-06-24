## Trunk week 2 report

Week 2 was filled with a lot of refactoring, cleanup, and very important systems.
This includes a full style shift, a design change, and more.

## Week 2

# NT style codebase

This is arguably the biggest change made.

I have completely changed the codebase, type-aliases and all, to NT style.

It's not to be compatiable with React or NT, I just really like the style.

So now most of the codebase is 'CAPCASE' type-aliases.

Along with this, I have shifted functions to PascalCase.

BEFORE:
'u8 test_function_some(char msg)'

NOW:
'BYTE TestFunctionSome(CHAR msg)'

# Seperating the kernel name

Before, it was all Trunk.

The kernel did not have a special name, everything was under trunk.

However, this has been changed.

The 'product' name is 'Trunk', and the kernel name is 'CBK'

This reflects my new design choice, to shift it to a console-based gui os rather then a desktop

'cbk' = 'console based kernel'

# Cleanup

I have done some heavy changes to improve performance, readability, and more.

You can check commit history for a list of them.

# Memory Management

I have created a bare-bones memory management system.

It's based on React and Windows.

It's nothing special right now, I tried to get alloc API done, but i couldn't this week

So you cannot do 'kmalloc' yet!

ENDING VERSION FOR TRUNK AS OF WEEK 2:
0.15.15
