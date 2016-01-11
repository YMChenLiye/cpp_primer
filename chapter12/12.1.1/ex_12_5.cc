@Mooophy:

keyword explicit prevents automatic conversion from an initializer_list to StrBlob. This design choice would easy to use but hard to debug.

@pezy:

Pros

The compiler will not use this constructor in an automatic conversion.
We can realize clearly which class we have used.

Cons

We always uses the constructor to construct a temporary StrBlob object.
cannot use the copy form of initialization with an explicit constructor. not easy to use.


