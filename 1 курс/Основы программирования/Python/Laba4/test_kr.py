import pytest
import Laba4


def test_kruskal_normal():
    assert Laba4.kruskal({(1, 2): 1, (2, 3): 3, (1, 3): 4}) == {(1, 2): 1, (2, 3): 3}


def test_kruskal_zero_dict():
    assert Laba4.kruskal({}) == {}


def test_kruskal_not_ordered_dict():
    assert Laba4.kruskal({(1, 2): 9, (1, 3): 4, (2, 3): 5}) == {(1, 2): 9, (1, 3): 4}


def test_kruskal_wrong_edges():
    with pytest.raises(KeyError):
        Laba4.kruskal({(1, 2): 5, (4, 6): 5, (10, 15): 9})


def test_kruskal__negative_weight():
    assert Laba4.kruskal({(1, 2): -9, (1, 3): 8, (2, 3): 10}) == {(1, 2): -9, (1, 3): 8}
