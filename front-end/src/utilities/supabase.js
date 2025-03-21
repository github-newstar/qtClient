import { createClient } from '@supabase/supabase-js'
const supabaseUrl = 'https://iilsqvebuwqedfuuwxba.supabase.co'
const supabaseKey = `eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImlpbHNxdmVidXdxZWRmdXV3eGJhIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDI1NTIxNDIsImV4cCI6MjA1ODEyODE0Mn0.vaZietmKP5JjufaMccsXaj4qeMi__1dkpzLsD-Ncy4Q`
const supabase = createClient(supabaseUrl, supabaseKey)
export default supabase
