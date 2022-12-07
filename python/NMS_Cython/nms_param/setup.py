from distutils.core import setup
from Cython.Build import cythonize
from Cython.Distutils import build_ext
import numpy as np

setup(
      name = 'nms_module',
      ext_modules = cythonize('nms_params.pyx'),
      include_dirs=[np.get_include()]
      )