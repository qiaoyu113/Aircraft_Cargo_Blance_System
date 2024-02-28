# Software Part Of Aircraft Cargo auto Blance System

### Author：Yu Qiao & Yuhan Liu

### Introduce
---
Software Part (frontend) Of Aircraft Cargo auto Blance System

### Project architecture version
| Vue | EChart | TypeScript |
| ------ | ------ | ------ |
| v2.2.26 | v5.0.1 | v4.4.4 |

### Developer 👨‍💻
| Author | E-mail |
| ------ | ----- |
| [🤔️ Yu Qiao(Joey)](http://github.com/qiaoyu113) | 527324363@qq.com |
# 
### Membership 👩‍💻
| Team Member | E-mail |
| ------ | ------ |
| [Yuhan Liu](yuhanliu123@outlook.com) | yuhanliu123@outlook.com |
# 

# 
### Step 1
Install Enviorment (recommend to use 'yarn')
```
npm install
```
or
```
yarn install
```
# 
### Step 2
running project
# 
```
npm run serve
```
or
```
yarn run serve
```
# 

## Project Framework and Structure
```
frontend/
|-- node_modules/
|-- public/
|-- src/
|   |-- assets/
|   |-- components/
|   |   |-- echart/
|   |   |   |-- bottom/
|   |   |   |   |-- conveyorChart.vue         # Vue component for the conveyor chart.
|   |   |   |-- balance.vue                   # Vue component for balance display.
|   |   |   |-- light.vue                     # Vue component for light control.
|   |-- router/
|   |   |-- index.js                          # Router configuration for the application.
|   |-- store/
|   |   |-- index.js                          # Vuex store definition.
|   |-- views/
|       |-- index.vue                         # Main view component.
|       |-- simulation.vue                    # Simulation view component.
|       |-- status.vue                        # Status view component.
|-- App.vue                                   # Main application Vue component.
|-- main.js                                   # Entry point for the Vue application.
|-- .gitignore                                # Specifies intentionally untracked files to ignore.
|-- babel.config.js                           # Configuration for Babel.
|-- package-lock.json                         # Auto-generated file for npm to keep track of exact version of installed npm packages.
|-- package.json                              # Lists the packages your project depends on and their versions.
|-- README.md                                 # README file with project documentation.
```

####  All plug-ins and versions of front-end projects have been version-controlled. If version errors occur during installation, please delete package-lock.json