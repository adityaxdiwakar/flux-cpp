#include "nlohmann/json.hpp"
#include "instruments.hpp"

using namespace std;

void from_json(const nlohmann::json& j, fundamentals& f) {
  j.at("symbol").get_to(f.symbol);
  j.at("high52").get_to(f.high52);
  j.at("low52").get_to(f.low52);
  j.at("dividendAmount").get_to(f.dividend_amount);
  j.at("dividendYield").get_to(f.dividend_yield);
  j.at("dividendDate").get_to(f.dividend_date);
  j.at("peRatio").get_to(f.pe_ratio);
  j.at("pegRatio").get_to(f.peg_ratio);
  j.at("pbRatio").get_to(f.pb_ratio);
  j.at("prRatio").get_to(f.pr_ratio);
  j.at("pcfRatio").get_to(f.pcf_ratio);
  j.at("grossMarginTTM").get_to(f.gross_margin_ttm);
  j.at("grossMarginMRQ").get_to(f.gross_margin_mrq);
  j.at("netProfitMarginTTM").get_to(f.net_profit_margin_ttm);
  j.at("netProfitMarginMRQ").get_to(f.net_profit_margin_mrq);
  j.at("operatingMarginTTM").get_to(f.operating_margin_ttm);
  j.at("operatingMarginMRQ").get_to(f.operating_margin_mrq);
  j.at("returnOnEquity").get_to(f.return_on_equity);
  j.at("returnOnAssets").get_to(f.return_on_assets);
  j.at("returnOnInvestment").get_to(f.return_on_investment);
  j.at("quickRatio").get_to(f.quick_ratio);
  j.at("currentRatio").get_to(f.current_ratio);
  j.at("interestCoverage").get_to(f.interest_coverage);
  j.at("totalDebtToCapital").get_to(f.total_debt_to_capital);
  j.at("ltDebtToEquity").get_to(f.lt_debt_to_equity);
  j.at("totalDebtToEquity").get_to(f.total_debt_to_equity);
  j.at("epsTTM").get_to(f.eps_ttm);
  j.at("epsChangePercentTTM").get_to(f.eps_change_percent_ttm);
  j.at("epsChangeYear").get_to(f.eps_change_year);
  j.at("epsChange").get_to(f.eps_change);
  j.at("revChangeYear").get_to(f.rev_change_year);
  j.at("revChangeTTM").get_to(f.rev_change_ttm);
  j.at("revChangeIn").get_to(f.rev_change_in);
  j.at("sharesOutstanding").get_to(f.shares_outstanding);
  j.at("marketCapFloat").get_to(f.market_cap_float);
  j.at("marketCap").get_to(f.market_cap);
  j.at("bookValuePerShare").get_to(f.book_value_per_share);
  j.at("shortIntToFloat").get_to(f.short_int_to_float);
  j.at("shortIntDayToCover").get_to(f.short_int_day_to_cover);
  j.at("divGrowthRate3Year").get_to(f.div_growth_rate3_year);
  j.at("dividendPayAmount").get_to(f.dividend_pay_amount);
  j.at("dividendPayDate").get_to(f.dividend_pay_date);
  j.at("beta").get_to(f.beta);
  j.at("vol1DayAvg").get_to(f.vol1_day_avg);
  j.at("vol10DayAvg").get_to(f.vol10_day_avg);
  j.at("vol3MonthAvg").get_to(f.vol3_month_avg);
}

void to_json(nlohmann::json& j, const fundamentals& f) {
  j = {
    {"symbol", f.symbol},
    {"high52", f.high52},
    {"low52", f.low52},
    {"dividendAmount", f.dividend_amount},
    {"dividendYield", f.dividend_yield},
    {"dividendDate", f.dividend_date},
    {"peRatio", f.pe_ratio},
    {"pegRatio", f.peg_ratio},
    {"pbRatio", f.pb_ratio},
    {"prRatio", f.pr_ratio},
    {"pcfRatio", f.pcf_ratio},
    {"grossMarginTTM", f.gross_margin_ttm},
    {"grossMarginMRQ", f.gross_margin_mrq},
    {"netProfitMarginTTM", f.net_profit_margin_ttm},
    {"netProfitMarginMRQ", f.net_profit_margin_mrq},
    {"operatingMarginTTM", f.operating_margin_ttm},
    {"operatingMarginMRQ", f.operating_margin_mrq},
    {"returnOnEquity", f.return_on_equity},
    {"returnOnAssets", f.return_on_assets},
    {"returnOnInvestment", f.return_on_investment},
    {"quickRatio", f.quick_ratio},
    {"currentRatio", f.current_ratio},
    {"interestCoverage", f.interest_coverage},
    {"totalDebtToCapital", f.total_debt_to_capital},
    {"ltDebtToEquity", f.lt_debt_to_equity},
    {"totalDebtToEquity", f.total_debt_to_equity},
    {"epsTTM", f.eps_ttm},
    {"epsChangePercentTTM", f.eps_change_percent_ttm},
    {"epsChangeYear", f.eps_change_year},
    {"epsChange", f.eps_change},
    {"revChangeYear", f.rev_change_year},
    {"revChangeTTM", f.rev_change_ttm},
    {"revChangeIn", f.rev_change_in},
    {"sharesOutstanding", f.shares_outstanding},
    {"marketCapFloat", f.market_cap_float},
    {"marketCap", f.market_cap},
    {"bookValuePerShare", f.book_value_per_share},
    {"shortIntToFloat", f.short_int_to_float},
    {"shortIntDayToCover", f.short_int_day_to_cover},
    {"divGrowthRate3Year", f.div_growth_rate3_year},
    {"dividendPayAmount", f.dividend_pay_amount},
    {"dividendPayDate", f.dividend_pay_date},
    {"beta", f.beta},
    {"vol1DayAvg", f.vol1_day_avg},
    {"vol10DayAvg", f.vol10_day_avg},
    {"vol3MonthAvg", f.vol3_month_avg},
  };
}
