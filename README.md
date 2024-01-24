# Aircraft_Cargo_Blance_System
<details>
  <summary>点击展开详细内容</summary>

  <!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>GitHub README Language Switch</title>
  <style>
    .content {
      display: none;
    }
    .content.active {
      display: block;
    }
  </style>
</head>
<body>

<button onclick="toggleLanguage('english')">English</button>
<button onclick="toggleLanguage('chinese')">中文</button>

<div id="englishContent" class="content active">
  <!-- English content goes here -->
</div>

<div id="chineseContent" class="content">
  <!-- 中文内容放在这里 -->
</div>

<script>
  function toggleLanguage(language) {
    document.getElementById('englishContent').classList.toggle('active', language === 'english');
    document.getElementById('chineseContent').classList.toggle('active', language === 'chinese');
  }
</script>

</body>
</html>


</details>

## 项目简介
Aircraft Cargo Balance System 是一个用于飞机货物平衡管理的开源系统。该系统致力于帮助航空公司和货运运营商有效地规划和管理飞机上的货物分布，确保在飞行过程中保持良好的平衡，以提高飞行安全性和燃油效率。

## 功能特性
1. 货物管理： 提供直观的界面，让用户轻松添加、删除和编辑飞机上的货物信息。
2. 平衡计算： 基于飞机型号和货物分布，计算飞机的重心和平衡情况，确保在各个飞行阶段保持合理的平衡。
3. 报告生成： 生成详细的平衡报告，包括重心图、荷载图等，以供飞行员和地勤人员参考。

## 技术架构
1. 树莓派 (Raspberry Pi)
树莓派作为中央控制单元，负责接收和处理传感器数据，管理货物平衡系统，同时提供一个局域网服务器以供网页端访问。

传感器接口： 通过 GPIO 接口连接传感器，实时获取货物重量数据。
数据处理： 使用 Python 进行数据处理，计算平衡情况，生成重量热力图。
局域网服务器： 使用 Flask 或 FastAPI 框架搭建服务器，提供 API 供STM32和网页端访问。

2. STM32 微控制器
STM32负责实时控制传送带的移动，接收树莓派的指令来调整传送带的位置，确保货物保持平衡。

连接树莓派： 通过串口通信或其他通信协议，接收树莓派发送的平衡指令。
传送带控制： 控制传送带的电机，实现实时平衡调整。
传感器接口： 连接货物传感器，获取实时的货物位置信息。

3. 网页端 (Web)
网页端提供用户界面，允许用户监视货物平衡状态，实时查看重量热力图，以及进行远程控制。

前端界面： 使用 Vue 构建用户友好的界面，展示实时的货物平衡状态和重量热力图。
与树莓派通信： 通过使用 WebSocket 或 HTTP 轮询等方式，实时获取树莓派的数据。
用户控制： 允许用户通过界面发送控制指令，调整传送带位置，查看实时数据。


## 项目框架及结构
```
Aircraft_Cargo_Balance_System/
|-- backend/                  # 树莓派端代码
|   |-- app/                  # Flask或FastAPI应用代码
|   |   |-- __init__.py
|   |   |-- routes.py         # API路由
|   |   |-- controllers/      # 控制器，处理业务逻辑
|   |       |-- __init__.py
|   |       |-- balance_controller.py   # 平衡控制器
|   |-- config/               # 配置文件
|   |   |-- config.py         # 数据库和其他配置
|   |-- models/               # 数据库模型
|   |   |-- __init__.py
|   |   |-- cargo_model.py    # 货物模型
|   |   |-- balance_model.py  # 平衡信息模型
|   |-- utils/                # 工具函数
|       |-- __init__.py
|       |-- calculations.py   # 计算平衡等实用函数
|-- frontend/                 # 网页端代码
|   |-- public/
|   |-- src/
|   |   |-- components/       # React组件
|   |   |   |-- BalanceChart.js    # 重量热力图组件
|   |   |   |-- ControlPanel.js   # 控制面板组件
|   |   |-- pages/            # 页面组件
|   |   |   |-- Dashboard.js      # 仪表盘页面
|   |   |-- services/         # 前端服务
|   |   |   |-- api.js         # 与后端API通信
|   |   |-- App.js            # 主应用组件
|   |   |-- index.js          # 应用入口
|-- stm32/                    # STM32端代码
|   |-- src/                  # STM32源代码
|   |   |-- main.c            # 主程序入口
|   |   |-- communication.c   # 通信模块
|   |   |-- conveyor.c        # 传送带控制模块
|-- README.md                 # 项目说明文件
|-- LICENSE                   # 许可证文件
```