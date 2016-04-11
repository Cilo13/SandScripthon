#!/usr/bin/env python
#
# Unit tests for SandScript decorated functions from policy.py.
# Run: python policy_test.py before restarting the policy engine.

import unittest
import sys

import policy

class TestExampleField(unittest.TestCase):
    def test_field0(self):
        self.assertEqual(policy.Field("hello world", " ", 0), "hello")

    def test_field1(self):
        self.assertEqual(policy.Field("hello world", " ", 1), "world")

    def test_fielderr(self):
        self.assertEqual(policy.Field("hello world", " ", 2), None)

class TestExampleSum(unittest.TestCase):
    def test_oneplusone(self):
        self.assertEqual(policy.Sum(1, 1), 2)

    def test_maxint(self):
        self.assertEqual(policy.Sum(sys.maxint/2, sys.maxint/2), sys.maxint-1)

    def test_maxlong(self):
        self.assertEqual(policy.Sum(sys.maxsize/2, sys.maxsize/2), sys.maxsize-1)

if __name__ == "__main__":
    unittest.main()
