// filepath: c:\DocumentsOfEafen\【Project】programing\qtClient\backend\server.js
const express = require('express');
const cors = require('cors');
const app = express();

app.use(cors());
app.use(express.json()); // 添加这一行以解析JSON请求体

app.post('/get_code', (req, res) => {
    console.log('Received request:', req.body); // 打印请求体
    res.json({ message: 'Request received', data: req.body });
});

app.listen(8080, () => {
    console.log('Server is running on port 8080');
});