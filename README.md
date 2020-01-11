# md5_crypt
A high-level implementation of md5-crypt used to brute-force old linux passwords.

# The Algorithm
MD5-crypt is composed of 3 phases.
## Phase 1
The first phase is the setup phase, where we compute a starting intermediate value.

To compute this value, we need to understand ASCII. A nice table for this is provided at http://sticksandstones.kstrom.com/appen.html

The intermediate value will include the Alternate sum, which is simply md5(password + salt + password) where password is the user's ASCII password and salt is the randomized salt assigned.

After we have the alternate sum, we can compute the first intermediate value.

To form the first intermediate value, concatenate the following:
* password
* magic ("$1$" for the case of md5)
* salt
* take the number of characters in password, len_p, and concatonate len_p number of bytes of the alternate sum. If len_p is larger than the number of bytes in the alternate sum, then repeat the alternate sum
* for each bit in len_p from low to high (right to left):
  * if bit is set (1), then append a NUL byte
  * else append the first byte of the password

After you get the final concatonated string, take the md5 hash of it and you'll have the fist intermediate value.

