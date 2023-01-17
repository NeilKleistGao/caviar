# caviar
[![caviar linux tests](https://github.com/NeilKleistGao/caviar/actions/workflows/linux-test.yml/badge.svg?branch=main)](https://github.com/NeilKleistGao/caviar/actions/workflows/linux-test.yml)
[![caviar windows tests](https://github.com/NeilKleistGao/caviar/actions/workflows/windows-test.yml/badge.svg?branch=main)](https://github.com/NeilKleistGao/caviar/actions/workflows/windows-test.yml)

> New car, caviar, four star daydream and I think I will buy me a football team :)

![caviar.png](caviar.png)

A simple tool that helps you keep track of your personal expenses in Emacs.

## Install
- 1. Download the binary pack for your OS and make it accessible in terminals
- 2. Add `caviar.el` into your Emacs configurations like:
```lisp
(load-file "caviar.el")
```

## Format
```
Account[Card]: 114514CNY
Account[Wechat]: 19.19CNY
Plan: 2000CNY

** 2023-01-01
  Card:Income +100CNY
** 2023-01-02
  Card:Food -27.8CNY
  Wechat:LiveBonus +3.0CNY

---
Balance[Card]: 114,586.2CNY
Balance[Wechat]: 22.19CNY
Plan': 1,972.2CNY
```

## Commands
| Hotkeys   | Commands           |
| ---       | ---                |
| `C-c C-a` | Calculate Balances |

## TODO
- [ ] Add full units supports
- [ ] Sum of each category
- [ ] Better highlight in Emacs
