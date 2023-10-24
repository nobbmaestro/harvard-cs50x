import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from helpers import apology, login_required, lookup, usd
from werkzeug.security import check_password_hash, generate_password_hash

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Ensure non-empty symbol
        if not symbol:
            return apology("Missing symbol", 400)

        # Ensure non-empty number of shares
        elif not shares:
            return apology("Missing shares", 400)

        # Ensure valid symbol
        data = lookup(symbol)
        if not data:
            return apology("Invalid symbol", 400)

        # Ensure user liquidity
        transaction = float(shares) * float(data["price"])
        cash = db.execute("SELECT cash FROM users WHERE id=?",
                          session["user_id"])[0].get('cash', 0.0)
        if transaction > cash:
            return apology("Can't afford'", 400)

        # Insert transaction into user data
        else:
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                session["user_id"],
                symbol,
                float(shares),
                float(data["price"]),
            )
            return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute(
        "SELECT * FROM transactions WHERE user_id=?;",
        session["user_id"],
    )
    return render_template("history.html", transactions=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?",
                          request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
                rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Ensure non-emptry symbol
        if not symbol:
            return apology("Missing symbol", 400)

        # Ensure valid symbol
        data = lookup(symbol)
        if not data:
            return apology("Invalid symbol", 400)

        else:
            return render_template("/quoted.html", data=data)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 403)

        # Ensure that password matches confirmation
        elif password != confirmation:
            return apology("password must match", 403)

        # Check whether username already exists, insert to database if no matches exists
        result = db.execute("SELECT username FROM users WHERE username=?",
                            username)
        if result:
            return apology("username already exists", 403)

        else:
            # Create password hash
            hash = generate_password_hash(password)

            # Insert user into the database
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)",
                       username, hash)

        # Redirect iser to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
