from setuptools import setup

package_name = 'pbind_ctypes'

description = 'Python Bind'

file_packages = [
    package_name,
]

setup(
    name=package_name,
    version='0.0.0',
    packages=file_packages,
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='eprosima',
    maintainer_email='javierparis@eprosima.com',
    description=description,
    license='Apache License, Version 2.0',
    tests_require=['pytest'],
    test_suite='test',
    entry_points={},
)
