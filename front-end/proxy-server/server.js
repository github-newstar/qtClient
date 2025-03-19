const express = require('express')
const axios = require('axios')
const cors = require('cors') // 引入 cors 中间件

const app = express()
const port = 3000 // 代理服务器监听的端口

// 使用 cors 中间件，允许来自前端应用的跨域请求
// 注意：在生产环境中，你需要更精确地配置允许的源
app.use(
  cors({
    origin: 'http://localhost:5173', // 允许你的前端应用访问
    methods: 'GET,HEAD,PUT,PATCH,POST,DELETE',
    credentials: true, // 如果需要处理 cookie 等凭证，需要设置为 true
  }),
)

// 解析请求体，以便处理 POST 等请求 (如果你的 /get_code 接口需要接收 POST 数据)
app.use(express.json())
app.use(express.urlencoded({ extended: true }))

// 定义一个代理路由，例如 /proxy-get-code
app.all('/proxy-get-code', async (req, res) => {
  const targetApiUrl = 'http://localhost:8080/get_code' // 目标 API 的完整 URL

  try {
    const response = await axios({
      method: req.method,
      url: targetApiUrl,
      headers: {
        ...req.headers,
        host: 'localhost:8080', // 设置目标 API 的 Host 头部
      },
      data: req.body,
    })
    res.status(response.status).json(response.data)
  } catch (error) {
    console.error('代理请求失败:', error)
    if (error.response) {
      res.status(error.response.status).json(error.response.data)
    } else {
      res.status(500).json({ message: '代理服务器发生错误' })
    }
  }
})

app.listen(port, () => {
  console.log(`代理服务器运行在 http://localhost:${port}`)
})
