#clecc
---------

Implementation of an elliptic curve cryptographic system assisted by GPGPU computation via CUDA.

##What?

Elliptic curve cryptography. It's this thing that... well when you take a finite field and you... I mean you have these numbers and you sort of... 

Here, [this page](http://www.dkrypt.com/home/ecc) can explain it far better than I ever could. The entire thing is based on the intractability of the discrete logarithm problem on an elliptic curve. As for why this works, please accept this incredibly abstract and belabored analogy:

* You have a circle cut into 32 equal sections. 
* I pick one section of the circle, you pick another section of the circle. 
* Your section is at most N-1 and at least 1 steps away from my section if I traverse one section at a time.
* Note that if you're 6 sections away from me then the relative position of your section to my section can also be described as (6) + 32^e where e is an integer exponent.
* I mean, you could even be (-26) - 32^e sections away from me since it's a circle and all.

Now because we're dealing with a simple circle in this example, even with a huge exponent it's fairly easy to notice the pattern of repetition if we know the total number of segments. However, elliptic curves over finite fields have an interesting property where this sort of multiplication doesn't result in the same number each time it goes around. In fact, it's not guaranteed that you will _ever_ get the same number again if you continuously multiply by the same value.

##Why?

The only real reason to do anything, I suppose: to learn. I'd always been curious about how AES works under the hood and while any discrete math course will generally cover the RSA cryptosystem in depth, everybody knows AES is the cool kid (in so much as cryptosystems can be cool kids).

##How?

So here's the deal. I've done OpenGL in the past for small projects and little test applications. I've used CUDA before for a couple fluid physics simulations and some really simple numerical analysis. So naturally my intention is to mash together these two libraries until the twisted wreckage produces some eye-pleasing visualizations of the cryptosystem's internal processes. 

