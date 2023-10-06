
# slgltf


---------------------------------------------------------------------
## Table of contents

* [Install from pypi](#install-from-pypi)
* [Local Build](#local-build)
* [Administration](#administration)
* [Examples](#examples)
* [References](#references)

&nbsp;


---------------------------------------------------------------------
## Install from pypi

    Install dependencies (see below) then run...

    $ pip install slgltf

&nbsp;


---------------------------------------------------------------------
## Local Build

### Windows dependencies

- Install [CMake](https://cmake.org/download/)
- Install [git](https://git-scm.com/downloads)
- Install [boost](https://sourceforge.net/projects/boost/files/boost-binaries/)
- Install [Visual Studio 2017](https://visualstudio.microsoft.com/downloads/). *The free **Community Edition** is fine*


### Linux dependencies

    $ sudo apt-get update
    $ sudo apt-get -yq install build-essential git cmake libboost-all-dev doxygen graphviz go-md2man
    $ sudo apt-get -yq install python3 python3-pip python3-python11
    $ python3 -m pip install scikit-build


### Local Build / Install

    $ python3 -m pip install .

OR

    $ pip3 install .


### Uninstall

    $ pip3 uninstall -y slgltf


### Create wheel

    Software dist
    $ python3 setup.py sdist

    Binary dist
    $ python3 setup.py bdist_wheel

OR

    $ pip3 wheel . --use-feature=in-tree-build

&nbsp;


---------------------------------------------------------------------
## Administration (Linux only)

Library commands, for once you have it installed

- Display help

    **$ slgltf help**

- Uninstall

    **$ sudo slgltf uninstall**

- Show installation roots

    **$ slgltf files**

- Get installation information.  (Change this info in **PROJECT.txt**)

    **$ slgltf info \<variable\>**

    variable = One of [name, description, url, version, build, company, author, lib, include, bin, share]

&nbsp;


---------------------------------------------------------------------
## Examples

``` Python

    import slgltf

    print(dir(slgltf))
    print("[%s] %s" % (slgltf.__name__, slgltf.__file__))
    print("slgltf version : %s [%s]" % (slgltf.__version__, slgltf.__build__))


```

&nbsp;


---------------------------------------------------------------------
## References

- cgltf
    - https://github.com/jkuhlmann/cgltf

- Python
    - https://www.python.org/

- CMake
    - https://cmake.org

- pip
    - https://pip.pypa.io/en/stable/

- git
    - https://git-scm.com/

- Boost
    - https://www.boost.org/

- Visual Studio
    - https://visualstudio.microsoft.com/

- Doxygen
    - https://github.com/doxygen/doxygen

- Graphviz
    - https://graphviz.org/

- Md2man
    - https://sunaku.github.io/md2man/man/man5/md2man.5.html
    - https://github.com/sunaku/md2man
