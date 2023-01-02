# caviar
> New car, caviar, four star daydream and I think I will buy me a football team :)

A simple tool that helps you keep track of your personal expenses in Emacs.

## Install
TODO

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
### Create Account
`account name balance filename`

Example: `account Wechat 10CNY test.fsd`

This is equal to:
```
Account[Wechat]: 10CNY
```
In the `fsd` file.

### Plan Expenses
`plan value filename`

Example: `plan 100CNY test.fsd`

This is equal to:
```
Plan: 100CNY
```
In the `fsd` file.

### Create Change
`change account type value filename`

Example: `change Alipay Food -10CNY test.fsd`

This is equal to:
```
** 2023-01-02 ; today
  Alipay:Food -10CNY
```
In the `fsd` file.

### Update
`update filename`

Recalculate parts like this:
```
---
Balance[Card]: 114,586.2CNY
Balance[Wechat]: 22.19CNY
Plan': 1,972.2CNY
```

## TODO
- [ ] Add optional arguments
- [ ] Mutiple currencies support
