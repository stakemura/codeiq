# -*- coding:utf-8 -*-

"""
@brief CodeIQ 'Sampling normal distribution' problem ( https://codeiq.jp/ace/stakemura/q514 )
@author Shintaro TAKEMURA (stakemura@gmail.com)

This code is public domain, no warranty expressed or implied,
Functionality is thought to be correct, but it's up to you to make
sure it does what you want.
"""

import os
import sys
import matplotlib.pyplot as plt
import numpy as np
from scipy.stats import norm


def draw_normal_hist(mu, sigma):
    t = norm(loc=mu, scale=sigma)
    x = np.linspace(60, 100, 10000)
    h = plt.plot(x, t.pdf(x), label='$\mu=%d$, $\sigma=%d$' % (mu, sigma), linewidth=2)


if __name__ == '__main__':
    from optparse import OptionParser

    parser = OptionParser()
    parser.add_option("-o", dest="output_file", action='store',
                      metavar='FILE', help="output image file (optional)")
    parser.add_option("--dpi", dest="dpi", action='store', metavar='DPI', type=float, default=72,
                      help="dots/inch for output image")

    (options, args) = parser.parse_args()

    plt.xticks(fontsize=15)
    plt.yticks(fontsize=15)
    plt.xlabel('$x$', fontsize=24)
    plt.ylabel('$f(x|\mu,\sigma)$', fontsize=24)
    plt.grid(True)
    plt.title('Probability density function', fontsize=18)

    draw_normal_hist(82, 5)
    draw_normal_hist(85, 8)

    plt.legend(fontsize=16, loc='upper left')

    if options.output_file:
        plt.savefig(options.output_file, dpi=options.dpi, transparent=True)
    else:
        plt.show()
