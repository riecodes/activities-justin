document.addEventListener("DOMContentLoaded", () => {
    const form = document.querySelector(".login__form");
    const eyeIcon = document.getElementById("login-eye");
    const passwordInput = document.getElementById("login-pass");

    // Toggle password visibility
    eyeIcon.addEventListener("click", () => {
        const isPassword = passwordInput.getAttribute("type") === "password";
        passwordInput.setAttribute("type", isPassword ? "text" : "password");
        eyeIcon.classList.toggle("ri-eye-line");
        eyeIcon.classList.toggle("ri-eye-off-line");
    });

    // Form validation and authentication
    form.addEventListener("submit", (event) => {
        event.preventDefault();

        const username = document.getElementById("login-email").value.trim();
        const password = document.getElementById("login-pass").value.trim();

        // Hardcoded credentials for validation
        const validUsername = "IIT406";
        const validPassword = "LETRAN";

        if (username === validUsername && password === validPassword) {
            alert("Login successful!");
            window.location.href = "../html/Home.html"; // Redirect to Home.html
        } else {
            alert("Invalid username or password. Please try again.");
        }
    });
});
