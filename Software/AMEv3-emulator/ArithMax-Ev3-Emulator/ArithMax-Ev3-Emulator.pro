#-------------------------------------------------
#
# Project created by QtCreator 2014-03-16T15:43:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArithMax-Ev3-Emulator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    arithmaxscreen.cpp \
    qamthread.cpp \
    amt.cpp \
    stn.c \
    amtmain.c \
    key.c \
    Eigenmath/zero.cpp \
    Eigenmath/versionProvider.cpp \
    Eigenmath/vectorize.cpp \
    Eigenmath/variables.cpp \
    Eigenmath/userfunc.cpp \
    Eigenmath/transpose.cpp \
    Eigenmath/transform.cpp \
    Eigenmath/test.cpp \
    Eigenmath/tensor.cpp \
    Eigenmath/taylor.cpp \
    Eigenmath/tanh.cpp \
    Eigenmath/tan.cpp \
    Eigenmath/symbol.cpp \
    Eigenmath/sum.cpp \
    Eigenmath/subst.cpp \
    Eigenmath/stack.cpp \
    Eigenmath/sinh.cpp \
    Eigenmath/sin.cpp \
    Eigenmath/simplify.cpp \
    Eigenmath/simfac.cpp \
    Eigenmath/sgn.cpp \
    Eigenmath/selftest.cpp \
    Eigenmath/scan.cpp \
    Eigenmath/run.cpp \
    Eigenmath/roots.cpp \
    Eigenmath/rewrite.cpp \
    Eigenmath/rect.cpp \
    Eigenmath/real.cpp \
    Eigenmath/rationalize.cpp \
    Eigenmath/quotient.cpp \
    Eigenmath/quickfactor.cpp \
    Eigenmath/qsub.cpp \
    Eigenmath/qpow.cpp \
    Eigenmath/qmul.cpp \
    Eigenmath/qdiv.cpp \
    Eigenmath/qadd.cpp \
    Eigenmath/product.cpp \
    Eigenmath/print.cpp \
    Eigenmath/primetab.cpp \
    Eigenmath/prime.cpp \
    Eigenmath/power.cpp \
    Eigenmath/pollard.cpp \
    Eigenmath/polar.cpp \
    Eigenmath/partition.cpp \
    Eigenmath/outer.cpp \
    Eigenmath/numerator.cpp \
    Eigenmath/nroots.cpp \
    Eigenmath/multiply.cpp \
    Eigenmath/mstr.cpp \
    Eigenmath/msqrt.cpp \
    Eigenmath/mscan.cpp \
    Eigenmath/mroot.cpp \
    Eigenmath/mprime.cpp \
    Eigenmath/mpow.cpp \
    Eigenmath/mod.cpp \
    Eigenmath/mmul.cpp \
    Eigenmath/mmodpow.cpp \
    Eigenmath/mini-test.cpp \
    Eigenmath/mgcd.cpp \
    Eigenmath/mfactor.cpp \
    Eigenmath/mcmp.cpp \
    Eigenmath/mag.cpp \
    Eigenmath/madd.cpp \
    Eigenmath/log.cpp \
    Eigenmath/list.cpp \
    Eigenmath/legendre.cpp \
    Eigenmath/leading.cpp \
    Eigenmath/lcm.cpp \
    Eigenmath/laplace.cpp \
    Eigenmath/laguerre.cpp \
    Eigenmath/itest.cpp \
    Eigenmath/itab.cpp \
    Eigenmath/isprime.cpp \
    Eigenmath/is.cpp \
    Eigenmath/inv.cpp \
    Eigenmath/integral.cpp \
    Eigenmath/inner.cpp \
    Eigenmath/init.cpp \
    Eigenmath/index.cpp \
    Eigenmath/imag.cpp \
    Eigenmath/history.cpp \
    Eigenmath/hilbert.cpp \
    Eigenmath/hermite.cpp \
    Eigenmath/guess.cpp \
    Eigenmath/gcd.cpp \
    Eigenmath/gamma.cpp \
    Eigenmath/for.cpp \
    Eigenmath/floor.cpp \
    Eigenmath/float.cpp \
    Eigenmath/find.cpp \
    Eigenmath/filter.cpp \
    Eigenmath/factors.cpp \
    Eigenmath/factorpoly.cpp \
    Eigenmath/factorial.cpp \
    Eigenmath/factor.cpp \
    Eigenmath/expsin.cpp \
    Eigenmath/expcos.cpp \
    Eigenmath/expand.cpp \
    Eigenmath/eval.cpp \
    Eigenmath/erfc.cpp \
    Eigenmath/erf.cpp \
    Eigenmath/emisc.cpp \
    Eigenmath/emain.cpp \
    Eigenmath/eigen.cpp \
    Eigenmath/dsolve.cpp \
    Eigenmath/dpow.cpp \
    Eigenmath/divisors.cpp \
    Eigenmath/distill.cpp \
    Eigenmath/display.cpp \
    Eigenmath/dirac.cpp \
    Eigenmath/det.cpp \
    Eigenmath/derivative.cpp \
    Eigenmath/denominator.cpp \
    Eigenmath/degree.cpp \
    Eigenmath/defint.cpp \
    Eigenmath/define.cpp \
    Eigenmath/decomp.cpp \
    Eigenmath/dConsole.cpp \
    Eigenmath/data.cpp \
    Eigenmath/cosh.cpp \
    Eigenmath/cos.cpp \
    Eigenmath/contract.cpp \
    Eigenmath/cons.cpp \
    Eigenmath/conj.cpp \
    Eigenmath/condense.cpp \
    Eigenmath/cofactor.cpp \
    Eigenmath/coeff.cpp \
    Eigenmath/clock.cpp \
    Eigenmath/clear.cpp \
    Eigenmath/circexp.cpp \
    Eigenmath/choose.cpp \
    Eigenmath/ceiling.cpp \
    Eigenmath/binomial.cpp \
    Eigenmath/bignum.cpp \
    Eigenmath/bessely.cpp \
    Eigenmath/besselj.cpp \
    Eigenmath/bake.cpp \
    Eigenmath/atomize.cpp \
    Eigenmath/arg.cpp \
    Eigenmath/arctanh.cpp \
    Eigenmath/arctan.cpp \
    Eigenmath/arcsinh.cpp \
    Eigenmath/arcsin.cpp \
    Eigenmath/arccosh.cpp \
    Eigenmath/arccos.cpp \
    Eigenmath/append.cpp \
    Eigenmath/alloc.cpp \
    Eigenmath/adj.cpp \
    Eigenmath/add.cpp \
    Eigenmath/abs.cpp \
    Eigenmath/aboutGUI.cpp

HEADERS  += mainwindow.h \
    arithmaxscreen.h \
    qamthread.h \
    amt.h \
    am.h \
    stn.h \
    main.h \
    Eigenmath/versionProvider.hpp \
    Eigenmath/stdafx.h \
    Eigenmath/setjmp.h \
    Eigenmath/selftest.h \
    Eigenmath/prototypes.h \
    Eigenmath/help.h \
    Eigenmath/graphicsProvider.hpp \
    Eigenmath/fileProvider.hpp \
    Eigenmath/defs.h \
    Eigenmath/dConsole.h \
    Eigenmath/aboutGUI.hpp

FORMS    += mainwindow.ui

OTHER_FILES += \
    Eigenmath/test-script.txt \
    Eigenmath/help.html
