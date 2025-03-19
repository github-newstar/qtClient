<template>
  <form
    class="w-1/2 flex flex-col justify-center items-center p-4 gap-2 shadow-bottom rounded-md"
    action="#"
    @submit.prevent="handleSubmit"
  >
    <div class="my-2 text-3xl font-semibold">
      <h1>注册</h1>
    </div>

    <!-- 用户名 -->
    <input type="text" required placeholder="用户名" class="input" v-model="user" />
    <!-- 邮箱 -->
    <label class="input validator">
      <svg class="h-[1em] opacity-50" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
        <g
          stroke-linejoin="round"
          stroke-linecap="round"
          stroke-width="2.5"
          fill="none"
          stroke="currentColor"
        >
          <rect width="20" height="16" x="2" y="4" rx="2"></rect>
          <path d="m22 7-8.97 5.7a1.94 1.94 0 0 1-2.06 0L2 7"></path>
        </g>
      </svg>
      <input type="email" placeholder="mail@site.com" required v-model="email" />
    </label>
    <div class="validator-hint hidden">请输入邮箱</div>
    <!-- 密码 -->
    <label class="input validator">
      <svg class="h-[1em] opacity-50" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
        <g
          stroke-linejoin="round"
          stroke-linecap="round"
          stroke-width="2.5"
          fill="none"
          stroke="currentColor"
        >
          <path
            d="M2.586 17.414A2 2 0 0 0 2 18.828V21a1 1 0 0 0 1 1h3a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h1a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h.172a2 2 0 0 0 1.414-.586l.814-.814a6.5 6.5 0 1 0-4-4z"
          ></path>
          <circle cx="16.5" cy="7.5" r=".5" fill="currentColor"></circle>
        </g>
      </svg>
      <input
        v-model="passwd"
        type="password"
        required
        placeholder="密码"
        minlength="8"
        pattern="(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,}"
        title="Must be more than 8 characters, including number, lowercase letter, uppercase letter"
      />
    </label>
    <p class="validator-hint hidden">
      Must be more than 8 characters, including
      <br />At least one number <br />At least one lowercase letter <br />At least one uppercase
      letter
    </p>
    <!-- 确认密码 -->
    <label class="input validator">
      <svg class="h-[1em] opacity-50" xmlns="http://www.w3.org/2000/svg" viewBox="0 0 24 24">
        <g
          stroke-linejoin="round"
          stroke-linecap="round"
          stroke-width="2.5"
          fill="none"
          stroke="currentColor"
        >
          <path
            d="M2.586 17.414A2 2 0 0 0 2 18.828V21a1 1 0 0 0 1 1h3a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h1a1 1 0 0 0 1-1v-1a1 1 0 0 1 1-1h.172a2 2 0 0 0 1.414-.586l.814-.814a6.5 6.5 0 1 0-4-4z"
          ></path>
          <circle cx="16.5" cy="7.5" r=".5" fill="currentColor"></circle>
        </g>
      </svg>
      <input
        @input="confirmPassword"
        v-model="confirm"
        type="password"
        required
        placeholder="确认密码"
        minlength="8"
        pattern="(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{8,}"
        ref="confirmInput"
        title="Must be more than 8 characters, including number, lowercase letter, uppercase letter"
      />
    </label>
    <p v-if="showConfirm" class="text-red-500 text-sm">您两次输入的密码不一致</p>
    <!-- 验证码 -->
    <div class="flex gap-1">
      <input v-model="varifycode" type="text" placeholder="请输入验证码" required class="input" />
      <button type="button" @click="handleVerifyEmail" class="btn btn-outline btn-primary">
        发送
      </button>
    </div>

    <!-- 按钮 -->
    <div class="flex gap-2">
      <button class="btn btn-outline btn-secondary">注册</button>
    </div>
    <!-- 注册成功提示 -->
    <div>
      <p v-show="showSuccess" class="text-green-500 text-center">注册成功</p>
    </div>
  </form>
  <button
    @click="forTest"
    class="bg-red-400 hover:bg-red-500 text-white font-bold py-2 px-4 rounded"
  >
    test
  </button>
</template>

<script setup>
import { ref } from 'vue'
import axios from 'axios'
import { useRouter } from 'vue-router'
import { uid } from 'uid'

const router = useRouter()

const user = ref('')
const email = ref('')
const passwd = ref('')
const confirm = ref('')
const varifycode = ref('')
const showSuccess = ref(false)
const showConfirm = ref(null)
const inputTimer = ref(null)
const confirmInput = ref(null)

// 确认密码一致
const confirmPassword = () => {
  // 清除定时器
  clearTimeout(inputTimer.value)
  inputTimer.value = setTimeout(() => {
    if (passwd.value == confirm.value) {
      showConfirm.value = false
    } else {
      showConfirm.value = true
    }
  }, 200)
}

// 发送验证码
const handleVerifyEmail = async () => {
  try {
    const response = await axios.post('http://localhost:3000/proxy-get-code', {
      email: email.value,
    })
    console.log(response)
  } catch (err) {
    console.log(err)
  }
}

// 发送新用户信息到服务器
const handleSubmit = async () => {
  try {
    //这里别忘了将代理服务器配置改一下
    const response = await axios.post('http://localhost:3000/proxy-get-code', {
      id: uid(),
      user: user.value,
      email: email.value,
      passwd: passwd.value,
      confirm: confirm.value,
    })
    console.log(response)
  } catch (err) {
    console.log(err)
  }
  // 确认密码一致
  if (passwd.value == confirm.value) {
    showSuccess.value = true
    setTimeout(() => {
      router.push('/login')
    }, 2000)
  } else {
    confirmInput.value.focus()
  }
}

// 测试用
const forTest = () => {}
</script>

<style lang="scss" scoped></style>
