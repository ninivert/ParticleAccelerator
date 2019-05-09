TEMPLATE = subdirs

SUBDIRS = \
	common \
	apps/exercices/exerciceP9 \
	apps/exercices/exerciceP10 \
	apps/exercices/exerciceP13 \
	apps/tests/testAccelerator \
	apps/tests/testBeam \
	apps/tests/testCircular \
	apps/tests/testConvert \
	apps/tests/testElement \
	apps/tests/testException \
	apps/tests/testFrodo \
	apps/tests/testParticle \
	apps/tests/testRenderer \
	apps/tests/testVector3D \
	apps/app

test/exercices/exerciceP9.depends = common
test/exercices/exerciceP10.depends = common
test/exercices/exerciceP13.depends = common
apps/tests/testAccelerator.depends = common
apps/tests/testBeam.depends = common
apps/tests/testCircular.depends = common
apps/tests/testConvert.depends = common
apps/tests/testElement.depends = common
apps/tests/testException.depends = common
apps/tests/testFrodo.depends = common
apps/tests/testParticle.depends = common
apps/tests/testRenderer.depends = common
apps/tests/testVector3D.depends = common
apps/app.depends = common
