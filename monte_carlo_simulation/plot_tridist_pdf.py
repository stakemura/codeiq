# -*- coding:utf-8 -*-

"""
@brief CodeIQ 'Sampling triangular distribution' problem ( https://codeiq.jp/ace/stakemura/q486 )
@author Shintaro TAKEMURA (stakemura@gmail.com)

This code is public domain, no warranty expressed or implied,
Functionality is thought to be correct, but it's up to you to make
sure it does what you want.
"""

import os
import sys
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import triang


def draw_triangle_hist(a, b, c):
    scale = float(b - a)
    t = triang(float(c - a) / scale, loc=float(a), scale=scale)
    x = np.linspace(60, 100, 10000)
    h = plt.plot(x, t.pdf(x), label='$a=%d$, $b=%d$, $c=%d$' % (a, b, c), linewidth=2)


if __name__ == '__main__':
    from optparse import OptionParser

    parser = OptionParser()
    parser.add_option("-o", dest="output_file", action='store',
                      metavar='FILE', help="output image file (optional)")
    parser.add_option("--dpi", dest="dpi", action='store', metavar='DPI', type=float, default=72.0,
                      help="dots/inch for output image")

    (options, args) = parser.parse_args()

    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)
    plt.xlabel('$x$', fontsize=24)
    plt.ylabel('$f(x|a,b,c)$', fontsize=24)
    plt.grid(True)
    plt.title('Probability density function', fontsize=18)

    draw_triangle_hist(61, 100, 85)
    draw_triangle_hist(75, 97, 82)

    plt.legend(fontsize=16, loc='upper left')

    if options.output_file:
        plt.savefig(options.output_file, dpi=options.dpi, transparent=True)
    else:
        plt.show()
