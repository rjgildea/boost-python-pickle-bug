# "Incomplete pickle support" Boost.Python bug using Python 3.11

This repo provides examples to reproduce a bug encountered using Boost.Python with Python 3.11.
It appears to be related to following change introduced in Python 3.11:
> [bpo-26579](https://bugs.python.org/issue?@action=redirect&bpo=26579): Added `object.__getstate__` which provides the default implementation of the `__getstate__()` method.

## Build using Python 3.11 environment

```
$ mamba create -n boost-py311 python=3.11 boost=1.82.0 boost-cpp=1.82.0 -y
$ mamba activate boost-py311
```

```
$ mkdir _build_py311
$ cd _build_py311
$ cmake .. \
  -DPYTHON_INCLUDE_DIR=$(python -c "import sysconfig; print(sysconfig.get_path('include'))") \
  -DPYTHON_LIBRARY=$(python -c "import sysconfig; print(sysconfig.get_config_var('LIBDIR'))")
$ make
```

```
$ PYTHONPATH=$PWD; python ../greeting.py
Hello California
getattr(hw, '__getstate__', None)=<built-in method __getstate__ of HelloWorld object at 0x7f076de19d50>
hw.__dict__={'country': 'California'}
Traceback (most recent call last):
  File "/dls/science/users/hko55533/software/boost-python-bug/_build_py311/../greeting.py", line 19, in <module>
    pstr = pickle.dumps(hw)
           ^^^^^^^^^^^^^^^^
RuntimeError: Incomplete pickle support (__getstate_manages_dict__ not set)
```


## Build using Python 3.10 environment

```
$ mamba create -n boost-py310 python=3.10 boost=1.82.0 boost-cpp=1.82.0 -y
$ mamba activate boost-py310
```

```
$ cd ../
$ mkdir _build_py310
$ cd _build_py310
$ cmake .. \
  -DPYTHON_INCLUDE_DIR=$(python -c "import sysconfig; print(sysconfig.get_path('include'))") \
  -DPYTHON_LIBRARY=$(python -c "import sysconfig; print(sysconfig.get_config_var('LIBDIR'))")
$ make
```

```
$ PYTHONPATH=$PWD; python ../greeting.py
Hello California
getattr(hw, '__getstate__', None)=None
hw.__dict__={'country': 'California'}
Hello California
```
