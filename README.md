BREAD
=====

CLI tool for calculating a bread recipe [![Build Status](https://travis-ci.org/deltaskelta/bread.svg?branch=master)](https://travis-ci.org/deltaskelta/bread)

Usage:
======

bread takes 3 integer arguments in order `hydration` `total flour` and `salt content`

 ```bash
 bread 65 500 2
 ```

 Will yiled a recipe for making bread with 70% hydration (water is 70% of the flour by weight) with 500 grams of total flour and 2 percent salt.

 ```bash
Add (500.000000) grams of flour
Add (35000.000000) grams of water
Add (10.000000) grams of salt
 ```

Option: -s
========

`-s` is the only option for `bread`. Use `-s` if you are making bread with a starter. `-s` adds two more positional arguments to `bread` `starter weight` `starter hydration`

```bash
bread -s 100 50 65 500 2
```

Will yield a recipe for making bread with a 100gram starter that is 50% water with 65% total ydration, 500g total flour, and 2% salt.

```bash
Add (433.333344) grams of Flour
Add (291.666656) grams of water
Add (10.000000) grams of salt
```

`bread` also has a manpage. Ivoked by `man bread`

INFO
====

automake instructions found at https://robots.thoughtbot.com/the-magic-behind-configure-make-make-install to make this package

the only thing that it installs to the system is the bread binary in /usr/local/bin and the bread anpage which is at /usr/local/share/man/man1/bread.1

TODO
====

push it to a git repo and make sure the dists work
